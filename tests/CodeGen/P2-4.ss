(define (square n)
        (if (number? n)
                (* n n)
                'invalid_parameter
        )
)

(define (main)
        (display (square 7)) (newline)
)
