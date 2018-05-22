;; Project 3 Test 5

(define (arithmetic1 a b c d e)
  (+ (* (+ a b c) (- b d)) (- (* c d e) (/ a e)))
  )

(define (square b)
  (* b b)
  )

(define (babylonian s x)
  (if (< (- (square x) s) 0.0000000001)
      x
      (babylonian s (/ (+ x (/ s x)) 2.0))
      )
  )

(define (sqrt v)
  (if (< v 4)
      (babylonian v v)
      (babylonian v (/ v 2.0))
      )
  )

(define (main)
  (display (arithmetic1 1 2 4 8 16)) (newline)
  (display (arithmetic1 1 2 4 8 16)) (newline)
  (display (square 25)) (newline)
  (display (sqrt 4)) (newline)
  (display (sqrt 25)) (newline)
  (display (sqrt 144)) (newline)
  (display (sqrt 6.25)) (newline)
  )
