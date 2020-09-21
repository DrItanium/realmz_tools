; maya
; Copyright (c) 2012-2019, Joshua Scoggins
; All rights reserved.
;
; Redistribution and use in source and binary forms, with or without
; modification, are permitted provided that the following conditions are met:
;     * Redistributions of source code must retain the above copyright
;       notice, this list of conditions and the following disclaimer.
;     * Redistributions in binary form must reproduce the above copyright
;       notice, this list of conditions and the following disclaimer in the
;       documentation and/or other materials provided with the distribution.
;
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
; ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
; WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
; ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
; (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
; ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
; SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

; cgen.clp - helps streamline process of dynamic code generation
(deffunction paren-wrap
             ($?str)
             (str-cat "(" (expand$ ?str) ")"))
(deffunction space-concat
             ($?elements)
             (bind ?str
                   "")
             (progn$ (?element ?elements)
                     (bind ?str
                           (str-cat ?str
                                    " "
                                    (send ?element
                                          codegen))))
             ?str)
(deffunction quote
             ($?str)
             (str-cat "\"" (expand$ ?str) "\""))

(defmessage-handler USER build primary 
                    "anything that is not buildable should still respond to the build message"
                    () 
                    ; does nothing
                    )
(defmessage-handler LEXEME codegen primary () ?self)
(defmessage-handler NUMBER codegen primary () ?self)
(defclass buildable
  (is-a USER)
  (message-handler build primary)
  (message-handler codegen primary))
(defmessage-handler buildable build primary
                    ()
                    (build (send ?self
                                 codegen)))
(defclass expression
  (is-a USER)
  (message-handler codegen primary))
(defclass constant
  (is-a expression)
  (slot value
        (type LEXEME 
              NUMBER)
        (visibility public)
        (storage local)
        (default ?NONE))
  (message-handler codegen primary))
(defmessage-handler constant codegen primary
                    ()
                    (send (dynamic-get value)
                          codegen))

(defclass function-call
  (is-a expression)
  (slot function-name
        (type SYMBOL)
        (visibility public)
        (storage local)
        (default ?NONE))
  (multislot expression
             (allowed-classes expression)
             (visibility public)
             (storage local))
  (message-handler codegen primary))
(defmessage-handler function-call codegen primary
                    ()
                    (paren-wrap (dynamic-get function-name)
                                " "
                                (space-concat (dynamic-get expression))))
(defclass has-title
  (is-a USER)
  (slot title
        (type SYMBOL)
        (visibility public)
        (storage local)
        (default ?NONE)))
(defclass has-module-declaration
  (is-a USER)
  (slot module-separator
        (type LEXEME)
        (storage shared)
        (visibility public)
        (access read-only)
        (default "::"))
  (slot module-declaration
        (type SYMBOL)
        (visibility public)
        (storage local)
        (allowed-symbols FALSE)
        (default-dynamic FALSE))
  (message-handler construct-title primary))
(defmessage-handler has-module-declaration construct-title primary
                    (?title)
                    (if (dynamic-get module-declaration) then
                      (str-cat (dynamic-get module-declaration)
                               (dynamic-get module-separator)
                               ?title)
                      else
                      ?title))

(defclass simple-declaration
  (is-a has-title
        has-module-declaration
        buildable)
  (slot decl-title
        (type SYMBOL)
        (storage shared)
        (visibility public)
        (access read-only)
        (default PLEASE-OVERRIDE-IN-CHILD-CLASS))
  (message-handler generate-header primary)
  (message-handler codegen primary))
(defmessage-handler simple-declaration generate-header primary
                    ()
                    (str-cat (dynamic-get decl-title) 
                             " "
                             (send ?self
                                   construct-title
                                   (dynamic-get title))))
(defmessage-handler simple-declaration codegen primary
                    ()
                    (send ?self
                          generate-header))
(defclass has-doc-string
  (is-a USER)
  (slot documentation
        (type STRING
              SYMBOL)
        (visibility public)
        (storage local)
        (allowed-symbols FALSE)
        (default-dynamic FALSE))
  (message-handler generate-doc-string primary))
(defmessage-handler has-doc-string generate-doc-string primary
                    ()
                    (quote (if (dynamic-get documentation) then
                             (dynamic-get documentation)
                             else
                             "")))

(defclass declaration
  (is-a simple-declaration
        has-doc-string)
  (message-handler generate-header primary))
(defmessage-handler declaration generate-header primary
                    ()
                    (str-cat (call-next-handler) 
                             " "
                             (send ?self
                                   generate-doc-string)))
(defclass defgeneric
  (is-a declaration)
  (slot decl-title
        (source composite)
        (default defgeneric))

  (message-handler codegen primary))
(defmessage-handler defgeneric codegen primary
                    ()
                    (paren-wrap (call-next-handler)))



(defclass variable 
  (is-a expression
        has-title)
  (slot title-prefix
        (type LEXEME)
        (storage shared)
        (visibility public)
        (access read-only)
        (default ERROR-NOT-OVERWRITTEN-IN-CHILD))
  (message-handler codegen primary)
  (message-handler reference-variable primary))

(defmessage-handler variable codegen primary
                    ()
                    (send ?self
                          reference-variable))
(defmessage-handler variable reference-variable primary
                    ()
                    (format nil
                            "%s%s"
                            (dynamic-get title-prefix)
                            (dynamic-get title)))
(defclass singlefield-variable
  (is-a variable)
  (slot title-prefix
        (source composite)
        (default "?")))
(defclass multifield-variable
  (is-a variable)
  (slot title-prefix
        (source composite)
        (default "$?")))
(defclass argument
  (is-a variable))


(defclass defmethod-argument
  (is-a argument))



(defclass defmethod-singlefield-argument
  (is-a defmethod-argument
        singlefield-variable)
  (multislot conditional-elements
             (visibility public)
             (storage local))
  (message-handler codegen around))
(defmessage-handler defmethod-singlefield-argument codegen around
                    ()
                    (bind ?output 
                          (call-next-handler))
                    (if (not (empty$ (dynamic-get conditional-elements))) then
                      ; now we must generate the conditional elements one after another
                      (paren-wrap ?output 
                                  (space-concat (dynamic-get conditional-elements)))
                      else
                      ?output))
(defclass deffunction-argument
  (is-a argument))
(defclass deffunction-singlefield-argument
  (is-a deffunction-argument
        singlefield-variable))
(defclass deffunction-multifield-argument
  (is-a deffunction-argument
        multifield-variable))



(defclass defmethod-multifield-argument
  (is-a defmethod-argument
        multifield-variable))

(defclass has-arguments
  (is-a USER)
  (multislot arguments
             (type INSTANCE)
             (visibility public)
             (storage local))
  (message-handler build-argument-list primary))

(defmessage-handler has-arguments build-argument-list primary
                    ()
                    (space-concat (dynamic-get arguments)))

(defclass has-body
  (is-a USER)
  (multislot body
             (visibility public)
             (storage local))
  (message-handler build-body primary))
(defmessage-handler has-body build-body primary
                    ()
                    (space-concat (dynamic-get body)))

(defclass subroutine
  (is-a declaration
        has-arguments
        has-body)
  (message-handler codegen primary))

(defmessage-handler subroutine codegen primary
                    ()
                    (paren-wrap (call-next-handler)
                                " "
                                (paren-wrap (send ?self 
                                                  build-argument-list))
                                " "
                                (send ?self
                                      build-body)))

(defclass defmethod
  (is-a subroutine)
  (slot decl-title
        (source composite)
        (default defmethod))
  (multislot arguments
             (source composite)
             (allowed-classes defmethod-argument)))


(defclass deffunction
  (is-a subroutine)
  (slot decl-title
        (source composite)
        (default deffunction))
  (multislot arguments 
             (source composite)
             (allowed-classes deffunction-singlefield-argument))
  (slot wildcard-parameter
        (type INSTANCE
              SYMBOL)
        (storage local)
        (visibility public)
        (allowed-classes deffunction-multifield-argument)
        (allowed-symbols FALSE)
        (default-dynamic FALSE))
  (message-handler build-argument-list primary))

(defmessage-handler deffunction codegen around
                    ()
                    (space-concat (dynamic-get arguments)
                                  (if (dynamic-get wildcard-parameter) then
                                    (dynamic-get wildcard-parameter)
                                    else
                                    (create$))))



(defclass defglobal-entry
  (is-a has-title)
  (slot value
        (type INSTANCE)
        (allowed-classes expression)
        (storage local)
        (visibility public)
        (default ?NONE))
  (message-handler codegen primary))

(defmessage-handler defglobal-entry codegen primary
                    ()
                    (format nil
                            "?*%s* = %s"
                            (dynamic-get title)
                            (send (dynamic-get value)
                                  codegen)))

(defclass defglobal
  (is-a simple-declaration
        has-body)
  (slot decl-title
        (source composite)
        (default defglobal))
  (slot module-separator
        (source composite)
        (default " "))
  (multislot body
             (source composite)
             (allowed-classes defglobal-entry))
  (message-handler codegen primary))
(defmessage-handler defglobal codegen primary
                    ()
                    (paren-wrap (call-next-handler)
                                " "
                                (send ?self
                                      build-body)))
; TODO define constraint classes

(defclass rule-constraint
  (is-a USER)
  (role abstract)
  (pattern-match non-reactive))

(defclass unnamed-constraint 
  (is-a rule-constraint)
  (slot symbol
        (type LEXEME)
        (storage shared)
        (visibility public)
        (access read-only)
        (default OVERRIDE))
  (message-handler codegen primary))

(defmessage-handler unnamed-constraint codegen primary
                    ()
                    (dynamic-get symbol))

(defclass unnamed-singlefield-constraint
  (is-a unnamed-constraint)
  (role concrete)
  (pattern-match reactive)
  (slot symbol
        (source composite)
        (default "?")))

(defclass unnamed-multifield-constraint
  (is-a unnamed-constraint)
  (role concrete)
  (pattern-match reactive)
  (slot symbol
        (source composite)
        (default "$?")))

(defclass term-invocation
  (is-a USER)
  (slot invocation-symbol
        (type LEXEME)
        (storage shared)
        (visibility public)
        (access read-only)
        (default OVERRIDE))
  (slot function-call
        (type INSTANCE)
        (allowed-classes function-call)
        (storage local)
        (visibility public)
        (default ?NONE))
  (message-handler codegen primary))
(defmessage-handler term-invocation codegen primary
                    ()
                    (str-cat (dynamic-get invocation-symbol)
                             (send (dynamic-get function-call)
                                   codegen)))
(defclass boolean-term-invocation
  (is-a term-invocation)
  (slot invocation-symbol
        (source composite)
        (default ":")))
(defclass equality-term-invocation
  (is-a term-invocation)
  (slot invocation-symbol
        (source composite)
        (default "=")))


(defclass connected-rule-constraint
  (is-a rule-constraint))

(defclass defrule-argument
  (is-a argument))
(defclass defrule-singlefield-argument
  (is-a defrule-argument
        singlefield-variable))
(defclass defrule-multifield-argument
  (is-a defrule-argument
        multifield-variable))
(defclass single-rule-constraint 
  (is-a connected-rule-constraint)
  (role concrete)
  (pattern-match reactive)
  (slot match-false
        (type SYMBOL)
        (visibility public)
        (storage local)
        (allowed-symbols FALSE
                         TRUE))
  (slot term
        (type NUMBER
              LEXEME
              INSTANCE)
        (allowed-classes defrule-argument 
                         singlefield-variable)
        (visibility public)
        (storage local)
        (default ?NONE))
  (message-handler codegen primary))
(defmessage-handler single-rule-constraint codegen primary
                    ()
                    (str-cat (if (dynamic-get match-false) then
                               "~"
                               else
                               "")
                             (send (dynamic-get term)
                                   codegen)))

(defclass binary-connected-rule-constraint
  (is-a connected-rule-constraint)
  (slot connectivity-symbol
        (type LEXEME)
        (storage shared)
        (visibility public)
        (default OVERRIDE))
  (slot single-constraint
        (type INSTANCE)
        (allowed-classes single-rule-constraint)
        (storage local)
        (visibility public)
        (default ?NONE))
  (slot connected-constraint
        (type INSTANCE)
        (allowed-classes connected-rule-constraint)
        (storage local)
        (visibility public)
        (default ?NONE))
  (message-handler codegen primary))
(defmessage-handler binary-connected-rule-constraint codegen primary 
                    ()
                    (str-cat (send (dynamic-get single-constraint)
                                   codegen)
                             (dynamic-get connectivity-symbol)
                             (send (dynamic-get connected-constraint)
                                   codegen)))

(defclass and-connected-rule-constraint 
  (is-a binary-connected-rule-constraint)
  (role concrete)
  (pattern-match reactive)
  (slot connectivity-symbol
        (source composite)
        (default "&")))
(defclass or-connected-rule-constraint 
  (is-a binary-connected-rule-constraint)
  (role concrete)
  (pattern-match reactive)
  (slot connectivity-symbol
        (source composite)
        (default "|")))


(defclass conditional-element
  (is-a USER))
(defclass non-pattern-ce
  (is-a conditional-element)
  (slot action-kind
        (storage shared)
        (visibility public)
        (access read-only)
        (default OVERRIDE))
  (message-handler codegen primary))
(defmessage-handler non-pattern-ce codegen primary 
                    ()
                    (dynamic-get action-kind))
(defclass non-pattern-singlefield-ce
  (is-a non-pattern-ce)
  (slot conditional-element
        (storage local)
        (visibility public)
        (default ?NONE))
  (message-handler codegen primary))
(defmessage-handler non-pattern-singlefield-ce codegen primary
                    ()
                    (paren-wrap (call-next-handler)
                                " "
                                (send (dynamic-get conditional-element)
                                      codegen)))

(defclass not-ce 
  (is-a non-pattern-singlefield-ce)
  (slot action-kind
        (source composite)
        (default not)))
(defclass test-ce 
  (is-a non-pattern-singlefield-ce)
  (slot action-kind
        (source composite)
        (default test)))
(defclass non-pattern-multifield-ce
  (is-a non-pattern-ce)
  (multislot conditional-elements
             (storage local)
             (visibility public)
             (default ?NONE))
  (message-handler build-ces primary)
  (message-handler codegen primary))
(defmessage-handler non-pattern-multifield-ce codegen primary
                    ()
                    (paren-wrap (call-next-handler)
                                " "
                                (send ?self
                                      build-ces)))
(defmessage-handler non-pattern-multifield-ce build-ces primary
                    ()
                    (space-concat (dynamic-get conditional-element)))
(defclass and-ce 
  (is-a non-pattern-multifield-ce)
  (slot action-kind
        (source composite)
        (default and)))
(defclass or-ce 
  (is-a non-pattern-multifield-ce)
  (slot action-kind
        (source composite)
        (default or)))
(defclass logical-ce 
  (is-a non-pattern-multifield-ce)
  (slot action-kind
        (source composite)
        (default logical)))
(defclass exists-ce 
  (is-a non-pattern-multifield-ce)
  (slot action-kind
        (source composite)
        (default exists)))
(defclass forall-ce 
  (is-a non-pattern-multifield-ce)
  (slot action-kind
        (source composite)
        (default forall)))


(defclass assignable-pattern-conditional-element
  (is-a conditional-element)
  (slot bind-name
        (type SYMBOL)
        (storage local)
        (visibility public)
        (default-dynamic FALSE))
  (message-handler generate-binder primary)
  (message-handler codegen around))
(defmessage-handler assignable-pattern-conditional-element generate-binder primary
                    ()
                    (if (dynamic-get bind-name) then
                      (format nil
                              "?%s <-"
                              (dynamic-get bind-name))
                      else
                      ""))

(defmessage-handler assignable-pattern-conditional-element codegen around
                    ()
                    (format nil
                            "%s %s"
                            (send ?self
                                  generate-binder)
                            (call-next-handler)))

(defclass ordered-pattern-ce
  (is-a assignable-pattern-conditional-element)
  (slot symbol
        (type SYMBOL)
        (storage local)
        (visibility public)
        (default ?NONE))
  (multislot constraints
             (storage local)
             (visibility public))
  (message-handler build-constraints primary)
  (message-handler codegen primary))

(defmessage-handler ordered-pattern-ce codegen primary 
                    ()
                    (paren-wrap (dynamic-get symbol)
                                " "
                                (send ?self
                                      build-constraints)))

(defmessage-handler ordered-pattern-ce build-constraints primary
                    ()
                    (space-concat (dynamic-get constraints)))

(defclass lhs-slot
  (is-a USER)
  (slot slot-name
        (type SYMBOL)
        (storage local)
        (visibility public)
        (default ?NONE))
  (message-handler codegen primary))
(defclass singlefield-lhs-slot
  (is-a lhs-slot)
  (slot constraint
        (storage local)
        (visibility public)
        (default ?NONE))
  (message-handler codegen primary))
(defmessage-handler singlefield-lhs-slot codegen primary
                    ()
                    (paren-wrap (dynamic-get slot-name)
                                " "
                                (send (dynamic-get constraint)
                                      codegen)))
(defclass multifield-lhs-slot
  (is-a lhs-slot)
  (multislot constraints
             (storage local)
             (visibility public))
  (message-handler codegen primary))
(defmessage-handler multifield-lhs-slot codegen primary
                    ()
                    (paren-wrap (dynamic-get slot-name)
                                " "
                                (space-concat (dynamic-get constraints))))
(defclass template-pattern-ce 
  (is-a assignable-pattern-conditional-element)
  (slot deftemplate-name
        (type SYMBOL)
        (storage local)
        (visibility public)
        (default ?NONE))
  (multislot lhs-slots
             (allowed-classes lhs-slot)
             (storage local)
             (visibility public))
  (message-handler codegen primary))

(defmessage-handler template-pattern-ce codegen primary 
                    ()
                    (paren-wrap (dynamic-get deftemplate-name)
                                " "
                                (space-concat (dynamic-get lhs-slots))))

(defclass basic-attribute-constraint
  (is-a USER)
  (slot slot-name
        (type SYMBOL)
        (storage local)
        (visibility public)
        (default ?NONE))
  (message-handler codegen primary))

(defclass generic-attribute-constraint
  (is-a basic-attribute-constraint)
  (multislot constraints
             (storage local)
             (visibility public))
  (message-handler codegen primary))

(defmessage-handler generic-attribute-constraint codegen primary
                    ()
                    (paren-wrap (dynamic-get slot-name)
                                " "
                                (space-concat (dynamic-get constraints))))


(defclass fixed-attribute-constraint
  (is-a basic-attribute-constraint)
  (slot slot-name
        (source composite)
        (storage shared)
        (access read-only)
        (create-accessor read)
        (default OVERRIDE))
  (slot constraint
        (storage local)
        (visibility public)
        (default ?NONE))
  (message-handler codegen primary))

(defmessage-handler fixed-attribute-constraint codegen primary 
                    ()
                    (paren-wrap (dynamic-get slot-name)
                                " "
                                (send (dynamic-get constraint)
                                      codegen)))

(defclass isa-attribute-constraint
  (is-a fixed-attribute-constraint)
  (slot slot-name
        (source composite)
        (default is-a)))

(defclass name-attribute-constraint
  (is-a fixed-attribute-constraint)
  (slot slot-name
        (source composite)
        (default name)))

(defclass object-pattern-ce 
  (is-a assignable-pattern-conditional-element)
  (multislot attribute-constraints 
             (allowed-classes attribute-constraint)
             (storage local)
             (visibility public))
  (message-handler codegen primary))

(defmessage-handler template-pattern-ce codegen primary 
                    ()
                    (paren-wrap "object "
                                (space-concat (dynamic-get attribute-constraints))))
(defclass rule-property 
  (is-a USER)
  (slot slot-name 
        (type SYMBOL)
        (storage shared)
        (visibility public)
        (access read-only)
        (default OVERRIDE))
  (slot value
        (storage local)
        (visibility public)
        (default ?NONE))
  (message-handler codegen primary))
(defmessage-handler rule-property codegen primary
                    ()
                    (paren-wrap (dynamic-get slot-name)
                                " "
                                (dynamic-get value)))

(defclass salience-property
  (is-a rule-property)
  (slot slot-name
        (source composite)
        (default salience))
  (slot value
        (source composite)
        (type INTEGER)
        (default ?NONE)))

(defclass auto-focus-property
  (is-a rule-property)
  (slot slot-name
        (source composite)
        (default auto-focus))
  (slot value
        (source composite)
        (type SYMBOL)
        (allowed-symbols FALSE
                         TRUE)
        (default-dynamic FALSE)))

(defclass defrule
  (is-a declaration
        has-body)
  (multislot declarations
             (allowed-classes rule-property)
             (storage local)
             (visibility public))
  (multislot conditional-elements
             (allowed-classes conditional-element)
             (storage local)
             (visibility public))
  (slot decl-title 
        (source composite)
        (default defrule))
  (message-handler build-declarations primary)
  (message-handler build-ces primary)
  (message-handler codegen primary))
(defmessage-handler defrule build-ces primary
                    ()
                    (space-concat (dynamic-get conditional-elements)))
(defmessage-handler defrule build-declarations primary
                    ()
                    (if (not (empty$ (dynamic-get declarations))) then
                      (paren-wrap "declare "
                                  (space-concat (dynamic-get declarations)))
                      else
                      ""))
(defmessage-handler defrule codegen primary
                    ()
                    (paren-wrap (call-next-handler)
                                " "
                                (send ?self
                                      build-declarations)
                                " "
                                (send ?self
                                      build-ces)
                                " => "
                                (send ?self
                                      build-body)))

(defclass defclass 
  (is-a declaration)
  (multislot isa 
             (type SYMBOL
                   INSTANCE)
             (storage local)
             (visibility public)
             (cardinality 1 ?VARIABLE)
             (default ?NONE))
  (slot role
        (type SYMBOL)
        (allowed-symbols concrete
                         abstract)
        (storage local)
        (visibility public)
        (default-dynamic concrete))
  (slot pattern-match 
        (type SYMBOL)
        (allowed-symbols reactive
                         non-reactive)
        (storage local)
        (visibility public)
        (default-dynamic reactive))
  (multislot slots
             (storage local)
             (visibility public))
  (multislot handler-documentation
             (storage local)
             (visibility public))
  (message-handler codegen primary))
        
