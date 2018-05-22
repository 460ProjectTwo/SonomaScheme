;; Project 3 Test 4

(define (abs1 v)
  (if (> v 0)
      v
      (- 0 v)
      )
  )

(define (abs2 v)
  (if (number? v)
      (if (> v 0)
          v
          (- 0 v)
          )
      'NotNumeric
      )
  )

(define (main)
  (display (abs1 -5)) (newline)
  (display (abs1 5)) (newline)
  (display (abs2 -5)) (newline)
  (display (abs2 5)) (newline)
  (display (abs2 'x)) (newline)
  )
