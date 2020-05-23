(set-logic QF_NRA)
(declare-const a Real)
(assert (= a 2))
(assert
  (let ((b 10))
    (and
      (let ((b a))
        (= b 2))
      (= b 10))))
(check-sat)
(exit)
