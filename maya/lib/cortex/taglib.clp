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
(batch* fs.clp)
(batch* stages.clp)
(batch* cgen.clp)
(deffacts stage-layout
          (stage (current cgen)
                 (rest generate
                       correlate
                       associate
                       infer)))
(deffacts high-level-prop-construction-facts
          (make-object album from property-correlation "ALBUM")
          (make-object album-artist from property-correlation "ALBUMARTIST")
          (make-object artist from property-correlation "ARTIST")
          (make-object genre from property-correlation "GENRE"))
(deffacts cgen-requests
          (cgen list-all genre)
          (cgen list-all artist)
          (cgen list-all album))
(defrule cgen:generate-list-all-method
         (stage (current cgen))
         ?f <- (cgen list-all ?target)
         =>
         (retract ?f)
         (bind ?plural
               (str-cat ?target s))
         (bind ?title
               (str-cat list-all- ?plural))
         (bind ?objects
               (make-instance of defgeneric
                              (title ?title))
               (make-instance of defmethod
                              (title ?title)
                              (arguments (bind ?arg0
                                               (make-instance of defmethod-singlefield-argument 
                                                              (title router)
                                                              (conditional-elements SYMBOL))))
                              (body (bind ?call0
                                          (make-instance of function-call 
                                             (function-name generic-list-all)
                                             (expression (send ?arg0 
                                                                reference-variable)
                                                          (quote "List of " ?plural ": ")
                                                          ?target)))))
                                                        
               (make-instance of defmethod
                              (title ?title)
                              (arguments)
                              (body (bind ?call1
                                          (make-instance of function-call
                                                        (function-name ?title)
                                                        (expression t)))))
               ?arg0
               ?call0
               ?call1)
         (progn$ (?object ?objects)
                 (send ?object build)
                 (unmake-instance ?object)))
(defrule cgen:generate-put-into-rule
         (stage (current cgen))
         ?f <- (cgen put ?s0 into ?s1)
         =>
         (retract ?f)
         (bind ?s2 
               (sym-cat ?s0 s))
         (build (str-cat (format nil
                                 "(defrule put-%s-into-%s
                                           (stage (current associate))"
                                           ?s0
                                           ?s1)
                                 (format nil 
                                         "(object (is-a %s)
                                                  (files $? ?file $?)
                                                  (%s $?things)
                                                  (name ?%s))"
                                         ?s1
                                         ?s2
                                         ?s1)
                                 (format nil 
                                         "(object (is-a %s)
                                                  (files $? ?file $?)
                                                  (name ?%s))"
                                         ?s0
                                         ?s0)
                                 (format nil 
                                         "(not %s)"
                                         (bind ?k 
                                               (format nil 
                                                       "(added %s ?%s to %s ?%s)"
                                                       ?s0 ?s0
                                                       ?s1 ?s1)))
                                 "=>"
                                 (format nil
                                         "(assert %s)"
                                         ?k)
                                 (format nil
                                         "(modify-instance ?%s 
                                                           (%s $?things
                                                               ?%s)))"
                                 ?s1
                                 ?s2
                                 ?s0))))

(deffunction audio-propertiesp
             "Check and see if we got audio properties back from the given file"
             (?path)
             (not (empty$ (get-audio-properties ?path))))
(deffunction basic-tag-infop 
             "Check and see if we have basic tag info in the given file"
             (?path)
             (not (empty$ (get-basic-tag-info ?path))))
(deffunction tag-propertiesp
             "Check and see if we have tag properties in the given file"
             (?path)
             (not (empty$ (get-tag-properties ?path))))
(defclass file
  (is-a USER)
  (slot path
        (type LEXEME)
        (storage local)
        (visibility public)
        (default ?NONE))
  (slot basic-data
        (type INSTANCE
              SYMBOL)
        (storage local)
        (visibility public)
        (allowed-symbols FALSE))
  (slot audio-props 
        (type INSTANCE
              SYMBOL)
        (storage local)
        (visibility public)
        (allowed-symbols FALSE))
  (multislot properties
             (storage local)
             (visibility public)))

(defclass tag-property
  (is-a USER)
  (slot parent
        (type INSTANCE)
        (storage local)
        (visibility public)
        (default ?NONE))
  (slot key
        (type LEXEME)
        (storage local)
        (visibility public)
        (default ?NONE))
  (slot value 
        (type LEXEME)
        (storage local)
        (visibility public)
        (default ?NONE)))

(defclass basic-tag-data
  "Extract and save the basic tag data from an extractable file!"
  (is-a USER)
  (slot parent
        (type INSTANCE)
        (storage local)
        (visibility public)
        (default ?NONE))
  (slot title
        (type LEXEME)
        (storage local)
        (visibility public))
  (slot artist 
        (type LEXEME)
        (storage local)
        (visibility public))
  (slot album 
        (type LEXEME)
        (storage local)
        (visibility public))
  (slot year 
        (type NUMBER)
        (storage local)
        (visibility public))
  (slot track 
        (type NUMBER)
        (storage local)
        (visibility public))
  (slot genre 
        (type LEXEME)
        (storage local)
        (visibility public)))

(defclass audio-properties
  (is-a USER)
  (slot parent
        (type INSTANCE)
        (storage local)
        (visibility public)
        (default ?NONE))
  (slot bitrate 
        (type NUMBER)
        (storage local)
        (visibility public)
        (default ?NONE))
  (slot sample-rate 
        (type NUMBER)
        (storage local)
        (visibility public)
        (default ?NONE))
  (slot channels
        (type NUMBER)
        (storage local)
        (visibility public)
        (default ?NONE))
  (slot length
        (type NUMBER)
        (storage local)
        (visibility public)
        (default ?NONE))
  (slot mins 
        (type NUMBER)
        (storage local)
        (visibility public))
  (slot secs
        (type NUMBER)
        (storage local)
        (visibility public))
  (message-handler init after))
(defmessage-handler audio-properties init after
                    ()
                    (dynamic-put mins 
                                 (div (dynamic-get length)
                                      60))
                    (dynamic-put secs
                                 (mod (dynamic-get length)
                                      60)))

(defclass property-correlation
  "Associate tag properties with the same key and value"
  (is-a USER)
  (slot key
        (type LEXEME)
        (storage local)
        (visibility public)
        (default ?NONE))
  (slot value 
        (type LEXEME)
        (storage local)
        (visibility public)
        (default ?NONE))
  (multislot associated-files))

(defclass generic-correlation
  (is-a USER)
  (slot title
        (type LEXEME)
        (storage local)
        (visibility public)
        (default ?NONE))
  (multislot files
             (storage local)
             (visibility public)
             (default ?NONE))
  (message-handler get-generic-properties primary)
  (message-handler get-audio-props primary)
  (message-handler get-file-basic-data primary))
(defmessage-handler generic-correlation get-generic-properties primary
                    (?msg)
                    (bind ?output
                          (create$))
                    (progn$ (?f (dynamic-get files))
                            (bind ?output
                                  ?output
                                  (send ?f
                                        ?msg)))
                    ?output)
        
(defmessage-handler generic-correlation get-file-basic-data primary
                    ()
                    (send ?self
                          get-generic-properties
                          get-basic-data))

(defmessage-handler generic-correlation get-audio-props primary
                    ()
                    (send ?self
                          get-generic-properties
                          get-audio-props))

(deffacts cgen-album
          (cgen put genre into album)
          (cgen put artist into album))
(defclass album
  (is-a generic-correlation)
  (multislot artists
             (storage local)
             (visibility public))
  (multislot genres 
             (storage local)
             (visibility public))
  (slot length
        (type INTEGER)
        (storage local)
        (visibility public)
        (default-dynamic -1))
  (message-handler get-minutes primary)
  (message-handler get-seconds primary)
  (message-handler get-artist-names primary)
  (message-handler get-song-names primary)
  (message-handler init after))
(defmessage-handler album get-minutes primary
                    ()
                    (div (dynamic-get length) 60))
(defmessage-handler album get-remainder-seconds primary
                    ()
                    (mod (dynamic-get length) 60))
(defmessage-handler album init after
                    ()
                    (if (= -1 (dynamic-get length)) then
                      (bind ?count
                            0)
                      (progn$ (?f (dynamic-get files)) do
                              (bind ?count
                                    (+ ?count 
                                       (send (send ?f 
                                                   get-audio-props)
                                             get-length))))
                      (dynamic-put length
                                   ?count)))

(defmessage-handler album get-song-names primary
                    ()
                    (bind ?output
                          (create$))
                    (progn$ (?f (dynamic-get files))
                            (bind ?output
                                  ?output 
                                  (send (send ?f 
                                              get-basic-data)
                                        get-title)))
                    ?output)
(defmessage-handler album get-artist-names primary
                    ()
                    (bind ?output
                          (create$))
                    (progn$ (?a (dynamic-get artists))
                            (bind ?output
                                  ?output
                                  (send ?a 
                                        get-title)))
                    ?output)


(defclass album-artist
  (is-a generic-correlation))
(deffacts cgen-artist
          (cgen put genre into artist)
          (cgen put album into artist))
(defclass artist
  (is-a generic-correlation)
  (multislot albums
             (storage local)
             (visibility public))
  (multislot genres
             (storage local)
             (visibility public))
  (message-handler get-song-names primary)
  (message-handler get-album-names primary))
(defmessage-handler artist get-song-names primary
                    ()
                    ; to prevent DRY violations use the album's get-song-names message handler
                    (bind ?output
                          (create$))
                    (progn$ (?album (dynamic-get albums))
                            (bind ?output
                                  ?output
                                  (send ?album
                                        get-song-names)))
                    ?output)
(defmessage-handler artist get-album-names primary
                    ()
                    (bind ?output
                          (create$))
                    (progn$ (?album (dynamic-get albums))
                            (bind ?output
                                  ?output
                                  (send ?album 
                                        get-title)))
                    ?output)
(deffacts cgen-genre
          (cgen put album into genre)
          (cgen put artist into genre))

(defclass genre
  (is-a generic-correlation)
  (multislot albums 
             (storage local)
             (visibility public))
  (multislot artists
             (storage local)
             (visibility public)))


; testing routines
; testing rules
(defrule make-file-object
         (stage (current generate))
         ?f <- (file-check ?path)
         =>
         (retract ?f)
         (make-instance of file
                        (path ?path)))

(defrule make-basic-tag-data-fact
         (stage (current generate))
         (object (is-a file)
                 (path ?path)
                 (name ?parent))
         (not (basic-tag-info ?path
                              $?))
         (not (object (is-a basic-tag-data)
                      (parent ?parent)))
         (test (basic-tag-infop ?path))
         =>
         (assert (basic-tag-info ?path (get-basic-tag-info ?path))))
(defrule make-tag-property-fact
         (stage (current generate))
         (object (is-a file)
                 (path ?path)
                 (name ?parent))
         (test (tag-propertiesp ?path))
         =>
         (assert (tag-properties ?parent 
                                 (get-tag-properties ?path))))
(defrule construct-single-tag-property
         (stage (current generate))
         ?f <- (tag-properties ?parent
                               ?key ?value $?rest)
         =>
         (retract ?f)
         (assert (tag-properties ?parent 
                                 $?rest))
         (slot-insert$ ?parent
                       properties
                       1
                       (make-instance of tag-property
                                      (parent ?parent)
                                      (key ?key)
                                      (value ?value))))
(defrule done-with-tag-properties
         (stage (current generate))
         ?f <- (tag-properties ?)
         =>
         (retract ?f))
(defrule make-audio-property-data-fact
         (stage (current generate))
         (object (is-a file)
                 (path ?path)
                 (name ?parent))
         (test (audio-propertiesp ?path))
         (not (audio-propery-data ?parent $?))
         (not (object (is-a audio-properties)
                      (parent ?parent)))
         =>
         (assert (audio-property-data ?parent
                                      (get-audio-properties ?path))))


(defrule construct-basic-tag-data
         (stage (current generate))
         ?f <- (basic-tag-info ?path
                               ?title
                               ?artist
                               ?album
                               ?year
                               ?track
                               ?genre)
         (object (is-a file)
                 (path ?path)
                 (name ?parent))
         (not (object (is-a basic-tag-data)
                      (parent ?parent)))
         =>
         (retract ?f)
         (send ?parent
               put-basic-data
               (make-instance of basic-tag-data
                              (parent ?parent)
                              (title ?title)
                              (artist ?artist)
                              (album ?album)
                              (year ?year)
                              (track ?track)
                              (genre ?genre))))
(defrule construct-audio-properties
         (stage (current generate))
         ?f <- (audio-property-data ?parent
                                    ?bitrate
                                    ?sampleRate
                                    ?channels
                                    ?length)
         =>
         (retract ?f)
         (send ?parent
               put-audio-props
               (make-instance of audio-properties
                              (parent ?parent)
                              (bitrate ?bitrate)
                              (sample-rate ?sampleRate)
                              (channels ?channels)
                              (length ?length))))
(defrule eliminate-illegal-files
         (declare (salience -1))
         (stage (current generate))
         ?o <- (object (is-a file)
                       (name ?name)
                       (basic-data FALSE)
                       (audio-props FALSE)
                       (properties))
         =>
         (unmake-instance ?o))


(defrule construct-property-correlation
         (stage (current generate))
         (object (is-a tag-property)
                 (key ?key)
                 (value ?value)
                 (parent ?parent))
         (not (object (is-a property-correlation)
                      (key ?key)
                      (value ?value)))
         =>
         (assert (associated ?parent with 
                             (make-instance of property-correlation 
                                            (associated-files ?parent)
                                            (key ?key)
                                            (value ?value)))))
(defrule update-property-correlation
         (stage (current generate))
         (object (is-a tag-property)
                 (key ?key)
                 (value ?value)
                 (parent ?parent))
         ?obj <- (object (is-a property-correlation)
                         (key ?key)
                         (value ?value)
                         (associated-files $?files)
                         (name ?pc))
         (not (associated ?parent with ?pc))
         =>
         (assert (associated ?parent with ?pc))
         (modify-instance ?obj
                          (associated-files $?files 
                                            ?parent)))


(defrule translate-property-correlation
         "take a property-correlation and construct another object of it."
         (stage (current correlate))
         (make-object ?output-type from property-correlation ?key)
         (object (is-a property-correlation)
                 (key ?key)
                 (value ?title)
                 (associated-files $?files)
                 (name ?pc))
         =>
         (assert (translated property-correlation ?pc to 
                             (make-instance of ?output-type
                                            (title ?title)
                                            (files $?files)))))
; inference rules
(defrule album-by-a-single-artist
         (stage (current infer))
         (object (is-a album)
                 (title ?title)
                 (name ?album)
                 (artists ?artist))
         =>
         (assert (album ?album has single artist)))

(defrule album-is-compilation-album
         (stage (current infer))
         (object (is-a album)
                 (name ?album)
                 (title ?title)
                 (files $?files)
                 (artists $?artists))
         (test (> (length$ ?artists) 1))
         =>
         (assert (album ?album is compilation album)))

(defrule identify-songs-not-part-of-an-album
         (stage (current infer))
         (object (is-a file)
                 (name ?file)
                 (basic-data ~FALSE))
         (not (object (is-a album)
                      (files $? ?file $?)))
         =>
         (assert (song ?file has no album)))

(defrule identify-songs-with-only-audio-data
         (stage (current infer))
         (object (is-a file)
                 (name ?file)
                 (audio-props ~FALSE)
                 (basic-data FALSE)
                 (properties))
         =>
         (assert (file ?file is untagged)))


(deffunction generic-list-all
             (?router ?title ?kind)
             (printout ?router
                       ?title crlf)
             (do-for-all-instances ((?a ?kind))
                                   TRUE
                                   (printout ?router
                                             tab "- " ?a:title crlf)))


(defgeneric list-all-songs)
(defmethod list-all-songs
           ((?router SYMBOL))
           (generic-list-all ?router
                             "List of songs: "
                             basic-tag-data))
(defmethod list-all-songs
           ()
           (list-all-songs t))


(deffunction list-all-tag-kinds
             (?router)
             (printout ?router
                       "List of all acquired tag properties: " crlf)
             (bind ?collection
                   (create$))
             (do-for-all-instances ((?a property-correlation))
                                   (not (member$ ?a:key
                                                 ?collection))
                                   (bind ?collection
                                         ?collection
                                         ?a:key)
                                   (printout ?router
                                             tab "- " ?a:key crlf)))
(deffunction list-property-correlation-data
             (?router ?key)
             (printout ?router
                       "List of property correlation values with key " ?key crlf)
             (bind ?lookup-key 
                   (if (stringp ?key) then
                    ?key
                    else
                    (str-cat ?key)))
                        
             (do-for-all-instances ((?a property-correlation))
                                   (eq ?a:key
                                       ?lookup-key)
                                   (printout ?router
                                             tab "- " ?a:value crlf)))
(deffunction list-all-songs-by-artist
             (?router ?artist)
             (printout ?router
                       "List of songs by artist " ?artist crlf)
             (do-for-all-instances ((?a artist))
                                   (eq ?a:title
                                       ?artist)
                                   (progn$ (?song (send ?a 
                                                        get-song-names))
                                           (printout ?router
                                                     tab "- " ?song crlf))))

            

(deffunction assert-file-facts
             (?path)
             (progn$ (?p (get-recursive-directory-contents ?path))
                     (assert (file-check ?p))))
(deffunction process-media
             "Convinence method for constructing knowledge about a media library (or multiple)"
             (?first $?rest)
             (reset)
             (assert-file-facts ?first)
             (progn$ (?root ?rest)
                     (assert-file-facts ?root))
             (run))
