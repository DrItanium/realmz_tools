(deffunction generate-registration-code
             "Reverse engineered using ghidra"
             (?snum)
             (- (* (+ (- (right-shift (+ (integer (/ ?snum 6))
                                         (right-shift ?snum 31))
                                      2)
                         (right-shift ?snum 31))
                      48)
                   14)
                28))
(defglobal MAIN
           ?*serial-number* = 0)
(printout t "Serial Number: ")
(bind ?*serial-number*
      (read))
(printout t "Serial Number entered is: " ?*serial-number* crlf)
(printout t "Registration Code: " 
          (generate-registration-code ?*serial-number*) crlf)
(exit)
