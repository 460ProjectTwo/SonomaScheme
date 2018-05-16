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
)
