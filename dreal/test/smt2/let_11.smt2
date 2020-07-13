(set-logic QF_NRA)
(declare-const a Real)
(assert (= a 2))
(assert
  (let ((b (= 2 2))
        (c (= a 2)))
    (and b c)))
(check-sat)
(exit)
