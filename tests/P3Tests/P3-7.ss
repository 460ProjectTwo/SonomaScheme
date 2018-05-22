;; Project 3 Test 7

(define (iftest a b c)
  (if (and (= a b) (= b c))
      'all_the_same
      (if (not (or (> a b) (> b c)))
          'in_ascending_order
          (if (not (< a c))
              'in_decscending_order
              'three_values_passed
              )
          )
      )
  )

(define (main)
  (display (iftest 10 15 20)) (newline)
  (display (iftest 10 10 10)) (newline)
  (display (iftest 20 15 10)) (newline)
  (display (iftest 15 10 20)) (newline)
  )
