;; Project 3 Test 6

(define (predicates x)
  (if (string? x)
      "Is a string"
      (if (null? x)
          "Is null"
          (if (symbol? x)
              "Is a symbol"
              (if (list? x)
                  "Is a list"
                  (if (zero? x)
                      "Is zero"
                      (if (number? x)
                          "Is a number"
                          "Is a USO"
                          )
                      )
                  )
              )
          )
      )
  )

(define (main)
  (display (predicates 0)) (newline)
  (display (predicates (+ 5 6))) (newline)
  (display (predicates 'hello)) (newline)
  (display (predicates '(a b c))) (newline)
  (display (predicates '())) (newline)
  (display (predicates "hello world")) (newline)
  )
