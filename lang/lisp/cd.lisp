(defun sum (a b)
  (+ a b))

(let ((x 10) (y 20))
  (sum x y))

(sum 1 2)
(dotimes (x 10) (format t "~d " x))

(getf (list :a 1 :b 2 :c 3) :a)
