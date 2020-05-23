(set-logic QF_NRA)
(declare-const a Real)
(assert (= a 2))
(assert
  (let ((b a))
    (and
      (let ((b 10))
        (= b 10))
      (= b 2))))
(check-sat)
(exit)
