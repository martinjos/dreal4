;; Author: Tristan Knoth
(set-logic QF_NRA)
(declare-fun p0 () Real [0, 100])
(declare-fun p1 () Real [0, 100])
(declare-fun p2 () Real [0, 100])
(declare-fun p3 () Real [0, 100])
(declare-fun p4 () Real [0, 100])
(declare-fun battery_charge_rate_fly () Real)
(declare-fun battery_charge_rate_hover () Real)
(declare-fun battery_charging_rate () Real)
(declare-fun drone_velocity () Real)
(declare-fun queue_data_rate () Real)
(declare-fun queue_upload_rate () Real)
(declare-fun s0_loc () Real [10.0, 10.0])
(declare-fun s1_loc () Real [20.0, 20.0])
(assert (= battery_charge_rate_fly -1.0))
(assert (= battery_charge_rate_hover -1.0))
(assert (= battery_charging_rate 50.0))
(assert (= drone_velocity 10.0))
(assert (= queue_data_rate 1.0))
(assert (= queue_upload_rate 50.0))
(declare-fun x0_2 () Real)
(declare-fun x1_2 () Real)
(declare-fun x2_2 () Real)
(declare-fun x3_2 () Real)
(declare-fun bi_2 () Real)
(declare-fun b0_2 () Real)
(declare-fun b1_2 () Real)
(declare-fun b2_2 () Real)
(declare-fun b3_2 () Real)
(declare-fun s0_qi_2 () Real)
(declare-fun s0_q0_2 () Real)
(declare-fun s0_q1_2 () Real)
(declare-fun s0_q2_2 () Real)
(declare-fun s0_q3_2 () Real)
(declare-fun s1_qi_2 () Real)
(declare-fun s1_q0_2 () Real)
(declare-fun s1_q1_2 () Real)
(declare-fun s1_q2_2 () Real)
(declare-fun s1_q3_2 () Real)
(declare-fun t0_2 () Real)
(declare-fun t1_2 () Real)
(declare-fun t2_2 () Real)
(declare-fun t3_2 () Real)
(declare-fun bc_2 () Real)
(declare-fun s0_qc_2 () Real)
(declare-fun s1_qc_2 () Real)
(assert (>= t0_2 0.0))
(assert (>= t1_2 0.0))
(assert (>= t2_2 0.0))
(assert (>= t3_2 0.0))
(assert (<= bi_2 100.0))
(assert (<= b0_2 100.0))
(assert (<= b1_2 100.0))
(assert (<= b2_2 100.0))
(assert (<= b3_2 100.0))
(assert (>= s0_qi_2 0.0))
(assert (>= s0_q0_2 0.0))
(assert (>= s0_q1_2 0.0))
(assert (>= s0_q2_2 0.0))
(assert (>= s0_q3_2 0.0))
(assert (>= s1_qi_2 0.0))
(assert (>= s1_q0_2 0.0))
(assert (>= s1_q1_2 0.0))
(assert (>= s1_q2_2 0.0))
(assert (>= s1_q3_2 0.0))
(assert (<= s0_qi_2 100.0))
(assert (<= s1_qi_2 100.0))
(declare-fun choice_2 () Int [0.0, 1.0])
;charging
(assert (= x0_2 0))
(assert (= b0_2 (+ bi_2 (* battery_charging_rate t0_2))))
(assert (= s0_q0_2 (+ s0_qi_2 (* queue_data_rate t0_2))))
(assert (= s1_q0_2 (+ s1_qi_2 (* queue_data_rate t0_2))))
(assert (and (=> (>= bi_2 p3) (= b0_2 bi_2)) (=> (< bi_2 p3) (= b0_2 p3))))
(assert (=> (< s1_qi_2 s0_qi_2) (= choice_2 0.0)))
(assert (=> (not (< s1_qi_2 s0_qi_2)) (= choice_2 1.0)))
(assert (> p1 p2))
(assert (= p0 10.0))
;flying to sensors
(assert (=> (= choice_2 0.0) (= x1_2 s0_loc)))
(assert (=> (= choice_2 1.0) (= x1_2 s1_loc)))
(assert (= x1_2 (+ x0_2 (* drone_velocity t1_2))))
(assert (= b1_2 (+ b0_2 (* battery_charge_rate_fly t1_2))))
(assert (= s0_q1_2 (+ s0_q0_2 (* queue_data_rate t1_2))))
(assert (= s1_q1_2 (+ s1_q0_2 (* queue_data_rate t1_2))))
;Collecting data
(assert (= x2_2 x1_2))
(assert (= b2_2 (+ b1_2 (* battery_charge_rate_hover t2_2))))
(assert (=> (= choice_2 0.0) (and (= s0_q2_2 (- s0_q1_2 (* queue_upload_rate t2_2))) (= s1_q2_2 (+ s1_q1_2 (* queue_data_rate t2_2))))))
(assert (=> (= choice_2 1.0) (and (= s1_q2_2 (- s1_q1_2 (* queue_upload_rate t2_2))) (= s0_q2_2 (+ s0_q1_2 (* queue_data_rate t2_2))))))
(assert (and (=> (>= b1_2 p4) (or (or (= b2_2 p4) (= s0_q2_2 0.0)) (= s1_q2_2 0.0))) (=> (< b1_2 p4) (= b2_2 b1_2))))
;flying back
(assert (= x3_2 0))
(assert (= x3_2 (+ x2_2 (- (* drone_velocity t3_2)))))
(assert (= b3_2 (+ b2_2 (* battery_charge_rate_fly t3_2))))
(assert (= s0_q3_2 (+ s0_q2_2 (* queue_data_rate t3_2))))
(assert (= s1_q3_2 (+ s1_q2_2 (* queue_data_rate t3_2))))
(assert (>= p1 p2))
(assert (= p0 bi_2))
(assert (= p1 s0_qi_2))
(assert (= (- p1 p2) s1_qi_2))
;Goal
(assert (and (and (> b0_2 0.0) (> b1_2 0.0) (> b2_2 0.0) (> b3_2 0.0) (< s0_q0_2 100.0) (< s0_q1_2 100.0) (< s0_q2_2 100.0) (< s0_q3_2 100.0) (< s1_q0_2 100.0) (< s1_q1_2 100.0) (< s1_q2_2 100.0) (< s1_q3_2 100.0))(or (and (and (>= b3_2 p0) (<= s0_q3_2 p1)) (<= (+ s1_q3_2 p2) p1)) (and (and (>= b3_2 p0) (<= s1_q3_2 p1)) (<= (+ s0_q3_2 p2) p1)))))
(declare-fun x0_1 () Real)
(declare-fun x1_1 () Real)
(declare-fun x2_1 () Real)
(declare-fun x3_1 () Real)
(declare-fun bi_1 () Real)
(declare-fun b0_1 () Real)
(declare-fun b1_1 () Real)
(declare-fun b2_1 () Real)
(declare-fun b3_1 () Real)
(declare-fun s0_qi_1 () Real)
(declare-fun s0_q0_1 () Real)
(declare-fun s0_q1_1 () Real)
(declare-fun s0_q2_1 () Real)
(declare-fun s0_q3_1 () Real)
(declare-fun s1_qi_1 () Real)
(declare-fun s1_q0_1 () Real)
(declare-fun s1_q1_1 () Real)
(declare-fun s1_q2_1 () Real)
(declare-fun s1_q3_1 () Real)
(declare-fun t0_1 () Real)
(declare-fun t1_1 () Real)
(declare-fun t2_1 () Real)
(declare-fun t3_1 () Real)
(declare-fun bc_1 () Real)
(declare-fun s0_qc_1 () Real)
(declare-fun s1_qc_1 () Real)
(assert (>= t0_1 0.0))
(assert (>= t1_1 0.0))
(assert (>= t2_1 0.0))
(assert (>= t3_1 0.0))
(assert (<= bi_1 100.0))
(assert (<= b0_1 100.0))
(assert (<= b1_1 100.0))
(assert (<= b2_1 100.0))
(assert (<= b3_1 100.0))
(assert (>= s0_qi_1 0.0))
(assert (>= s0_q0_1 0.0))
(assert (>= s0_q1_1 0.0))
(assert (>= s0_q2_1 0.0))
(assert (>= s0_q3_1 0.0))
(assert (>= s1_qi_1 0.0))
(assert (>= s1_q0_1 0.0))
(assert (>= s1_q1_1 0.0))
(assert (>= s1_q2_1 0.0))
(assert (>= s1_q3_1 0.0))
(assert (<= s0_qi_1 100.0))
(assert (<= s1_qi_1 100.0))
(declare-fun choice_1 () Int [0.0, 1.0])
;charging
(assert (= x0_1 0))
(assert (= b0_1 (+ bi_1 (* battery_charging_rate t0_1))))
(assert (= s0_q0_1 (+ s0_qi_1 (* queue_data_rate t0_1))))
(assert (= s1_q0_1 (+ s1_qi_1 (* queue_data_rate t0_1))))
(assert (and (=> (>= bi_1 p3) (= b0_1 bi_1)) (=> (< bi_1 p3) (= b0_1 p3))))
(assert (=> (< s1_qi_1 s0_qi_1) (= choice_1 0.0)))
(assert (=> (not (< s1_qi_1 s0_qi_1)) (= choice_1 1.0)))
(assert (> p1 p2))
(assert (= p0 10.0))
;flying to sensors
(assert (=> (= choice_1 0.0) (= x1_1 s0_loc)))
(assert (=> (= choice_1 1.0) (= x1_1 s1_loc)))
(assert (= x1_1 (+ x0_1 (* drone_velocity t1_1))))
(assert (= b1_1 (+ b0_1 (* battery_charge_rate_fly t1_1))))
(assert (= s0_q1_1 (+ s0_q0_1 (* queue_data_rate t1_1))))
(assert (= s1_q1_1 (+ s1_q0_1 (* queue_data_rate t1_1))))
;Collecting data
(assert (= x2_1 x1_1))
(assert (= b2_1 (+ b1_1 (* battery_charge_rate_hover t2_1))))
(assert (=> (= choice_1 0.0) (and (= s0_q2_1 (- s0_q1_1 (* queue_upload_rate t2_1))) (= s1_q2_1 (+ s1_q1_1 (* queue_data_rate t2_1))))))
(assert (=> (= choice_1 1.0) (and (= s1_q2_1 (- s1_q1_1 (* queue_upload_rate t2_1))) (= s0_q2_1 (+ s0_q1_1 (* queue_data_rate t2_1))))))
(assert (and (=> (>= b1_1 p4) (or (or (= b2_1 p4) (= s0_q2_1 0.0)) (= s1_q2_1 0.0))) (=> (< b1_1 p4) (= b2_1 b1_1))))
;flying back
(assert (= x3_1 0))
(assert (= x3_1 (+ x2_1 (- (* drone_velocity t3_1)))))
(assert (= b3_1 (+ b2_1 (* battery_charge_rate_fly t3_1))))
(assert (= s0_q3_1 (+ s0_q2_1 (* queue_data_rate t3_1))))
(assert (= s1_q3_1 (+ s1_q2_1 (* queue_data_rate t3_1))))
(assert (= p0 bi_1))
(assert (= (- p1 p2) s0_qi_1))
(assert (= p1 s1_qi_1))
;Goal
(assert(and (and (> b0_1 0.0) (> b1_1 0.0) (> b2_1 0.0) (> b3_1 0.0) (< s0_q0_1 100.0) (< s0_q1_1 100.0) (< s0_q2_1 100.0) (< s0_q3_1 100.0) (< s1_q0_1 100.0) (< s1_q1_1 100.0) (< s1_q2_1 100.0) (< s1_q3_1 100.0))(or (and (and (>= b3_1 p0) (<= s0_q3_1 p1)) (<= (+ s1_q3_1 p2) p1)) (and (and (>= b3_1 p0) (<= s1_q3_1 p1)) (<= (+ s0_q3_1 p2) p1)))))
(check-sat)
(exit)
