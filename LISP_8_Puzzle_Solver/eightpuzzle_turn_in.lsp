;;; authored by Colt Campbell
;;; CSCE 420-500
;;; February 2014

;;; This is a LISP program file that has functions to run
;;; a DFS, A* and greedy algorithm to solve the 8-puzzle
;;; A* and the greedy algorithms use heuristics to solve the 8-puzzle
;;; heuristic 1 = number of tiles out-of-place when compared to target
;;;	heuristic 2 = sum of manhattan distances
	
(defvar *goal* '(1 2 3 8 0 4 7 6 5))

(defvar *easy* '(1 3 4 8 6 2 7 0 5))

(defvar *medium* '(2 8 1 0 4 3 7 6 5))

(defvar *hard* '(5 6 7 4 0 8 3 2 1))	
	
(defun check-goal-state (state)
	(equal state '(1 2 3 8 0 4 7 6 5))
)

;;; finds the row column position of an element
;;; is there a way to make this less.... cluttered? 
;;; by making the loop into its own function?
(defun get-pos-element (element state)
	(let ((result '(0 0 )))
		(dotimes (i 3 result)
			(if (equal (car state) element)
				(setq result (append (list 0) (list i)))	
			)
			(setq state (cdr state))
		)
		(dotimes (i 3 result)
			(if (equal (car state) element)
				(setq result (append (list 1) (list i)))
			)
			(setq state (cdr state))
		)
		(dotimes (i 3 result)
			(if (equal (car state) element)
				(setq result (append (list 2) (list i)))
			)
			(setq state (cdr state))
		)
	)
)
 
(defun get-pos-blank (state)
	(get-pos-element '0 state)
)

;;; this function defers from get-pos-blank in that it gets the direct index
;;; of the blank space in the list 
(defun get-index (state)
	(let ((result 0))
		(dotimes (i 9 result)
			(if (equal (car state) '0)
				(setq result i)
			)
			(setq state (cdr state))
		)
	)
)

(defun possible-moves (blank-position)
	(let ((moves))
		(if (or (equal (car blank-position) '0) (equal (car blank-position) '1))
				(setq moves (append moves (list 'down)))
		)
		(if (or (equal (cadr blank-position) '0) (equal (cadr blank-position) '1))
			(setq moves (append moves (list 'right)))
		)
		(if (or (equal (car blank-position) '1) (equal (car blank-position) '2))
			(setq moves (append moves (list 'up)))
		)
		(if (or (equal (cadr blank-position) '1) (equal (cadr blank-position) '2))
			(setq moves (append moves (list 'left)))
		)
		moves	
	)	
)

(defun move-up (state)
	(let ((moves (possible-moves (get-pos-blank state))) (index-to-swap 0)
	(index-of-e 0) (can-up nil))
		;;; tells us if we can actually move up or not
		(dotimes (i (length moves) can-up)
			(if (equal (car moves) 'up)
				(setq can-up t)
			)
			;(print moves)
			(setq moves (cdr moves))
		)
		;;; gets the indices where we need to swap, and then performs swap
		;;; or move of the blank space
		(if (equal can-up t)
			(progn
				(setq index-of-e (get-index state))
				(setq index-to-swap (- index-of-e 3))
				(rotatef (nth index-of-e state) (nth index-to-swap state))
			)
			(print "The blank cannot move up here")
		)
		state
	)
)

(defun move-down (state)
	(let ((moves (possible-moves (get-pos-blank state))) (index-to-swap 0)
	(index-of-e 0) (can-down nil))
		;;; tells us if we can actually move down or not
		(dotimes (i (length moves) can-down)
			(if (equal (car moves) 'down)
				(setq can-down t)
			)
			;(print moves)
			(setq moves (cdr moves))
		)
		;;; gets the indices where we need to swap, and then performs swap
		;;; or move of the blank space
		(if (equal can-down t)
			(progn
				(setq index-of-e (get-index state))
				(setq index-to-swap (+ index-of-e 3))
				(rotatef (nth index-of-e state) (nth index-to-swap state))
			)
			(print "The blank cannot move down here")
		)
		state
	)
)

(defun move-left (state)
	(let ((moves (possible-moves (get-pos-blank state))) (index-to-swap 0)
	(index-of-e 0) (can-left nil))
		;;; tells us if we can actually move left or not
		(dotimes (i (length moves) can-left)
			(if (equal (car moves) 'left)
				(setq can-left t)
			)
			;(print moves)
			(setq moves (cdr moves))
		)
		;;; gets the indices where we need to swap, and then performs swap
		;;; or move of the blank space
		(if (equal can-left t)
			(progn
				(setq index-of-e (get-index state))
				(setq index-to-swap (- index-of-e 1))
				(rotatef (nth index-of-e state) (nth index-to-swap state))
			)
			(print "The blank cannot move left here")
		)
		state
	)
)

(defun move-right (state)
	(let ((moves (possible-moves (get-pos-blank state))) (index-to-swap 0)
	(index-of-e 0) (can-right nil))
		;;; tells us if we can actually move right or not
		(dotimes (i (length moves) can-right)
			(if (equal (car moves) 'right)
				(setq can-right t)
			)
			;(print moves)
			(setq moves (cdr moves))
		)
		;;; gets the indices where we need to swap, and then performs swap
		;;; or move of the blank space
		(if (equal can-right t)
			(progn
				(setq index-of-e (get-index state))
				(setq index-to-swap (+ index-of-e 1))
				(rotatef (nth index-of-e state) (nth index-to-swap state))
			)
			(print "The blank cannot move right here")
		)
		state
	)
)

;;; Heuristic 1
;;; the similarity function returns the number of tiles
;;; out of place in comparison to the target state
;;; the higher the number, the worse shape we're in compared
;;; to the goal state
(defun similarity (state)
	(let ((goal *goal*) (result 0))
		(dotimes (i 9 result)
			(if (not (or (equal (car state) (car goal)) (equal (car state) '0)))
				(setq result (+ result 1))
			)
			(setq goal (cdr goal))
			(setq state (cdr state))
		)
	)
)


;;; Heuristic 2
;;; The manhattan-distances function returns the 
;;; sum of the distances of the tiles from where they should be
(defun manhattan-distances (state)
	(let ((result 0) (currstate-element-pos '(0 0)) (goal-element-pos '(0 0))
	(y-state 0) (x-state 0) (x-goal 0) (y-goal 0))
		(dotimes (i 8 result)
			(setq currstate-element-pos (get-pos-element (+ i 1) state))
			(setq goal-element-pos (get-pos-element (+ i 1) *goal*))
			(setq y-state (car currstate-element-pos))
			(setq x-state (cadr currstate-element-pos))
			(setq y-goal (car goal-element-pos))
			(setq x-goal (cadr goal-element-pos))
			(setq result (+ result (abs (- y-state y-goal))))
			(setq result (+ result (abs (- x-state x-goal))))
		)
	)
)

(defun dupe (state node-list)
	(dolist (node node-list nil)
		(if (equal state (first node))
		(progn
			;(print (first node))
			(return-from dupe T)
		)
		)
	)
)
			
(defun nodes< (x y)
	(cond
		((null x) (not (null y)))
		((null y) nil)
		((= (second x) (second y)))
		(t (< (second x) (second y)))
	)
)

(defun nodes-a-star< (x y)
	(cond
		((null x) (not (null y)))
		((null y) nil)
		((= (+ (second x) (third x)) (+ (second y) (third y))))
		(t (< (+ (second x) (third x)) (+ (second y) (third y))))
	)
)
;once sorted, use setq vlist (sort vlist #'(lambda (x y) (< x y)))

;; for testing purposes
(defun node-list-generator ()
	(let
	((node) (node-list))
		(setq node (make-node '(1 2 3 8 4 0 7 6 5) '0 '0 '()))
		(setq node-list (make-node-list node))
		(setq node (generate-child-node node 'up 'heuristic-2))
		(setq node-list (add-node-to-list node node-list))
		(setq node (generate-child-node node 'down 'heuristic-2))
		(setq node-list (add-node-to-list node node-list))
		(setq node (generate-child-node node 'left 'heuristic-2))
		(setq node-list (add-node-to-list node node-list))
		(setq node (generate-child-node node 'down 'heuristic-2))
		(setq node-list (add-node-to-list node node-list))
		node-list
	)
)

;;for testing purposes
(defun sort-test ()
	(let 
	((node-list) (a-star-node-list))
		(setq node-list (node-list-generator))
		(setq a-star-node-list (node-list-generator))
		(setq node-list (sort node-list #'nodes<))
		(setq a-star-node-list (sort a-star-node-list #'nodes-a-star<))
		(print a-star-node-list)
		node-list
	)
)
	
(defun make-node (state heur depth path)
	(list state heur depth path)
)

(defun generate-child-node (parent-node move-action heur-option)
	(let ((child-node '(() 0 0 ())) (child-state) (child-heur 0) (child-depth 0) 
	(child-path) (temp-state '()) (temp-path '()))
		;(print parent-node)
		(setq temp-state (copy-tree (car parent-node)))
		(setq temp-path (copy-tree (cadddr parent-node)))
		(setq child-state temp-state)
		(cond 
			((equal move-action 'up)
				(progn
					(setq child-state (move-up child-state))
					(setq child-depth (+ (caddr parent-node) 1))
					(setq child-path (append temp-path (list 'up)))
					(cond
						((equal heur-option 'heuristic-1)
							(setq child-heur (similarity child-state))
						)
						((equal heur-option 'heuristic-2)
							(setq child-heur (manhattan-distances child-state))
						)
						((equal heur-option 'nil)
							(setq child-heur 0)
						)
					)
				)
			)
			((equal move-action 'down) 
				(progn
					(setq child-state (move-down child-state))
					(setq child-depth (+ (caddr parent-node) 1))
					(setq child-path (append temp-path (list 'down)))
					(cond
						((equal heur-option 'heuristic-1)
							(setq child-heur (similarity child-state))
						)
						((equal heur-option 'heuristic-2)
							(setq child-heur (manhattan-distances child-state))
						)
						((equal heur-option 'nil)
							(setq child-heur 0)
						)
					)
				)
			)
			((equal move-action 'left) 
				(progn
					(setq child-state (move-left child-state))
					(setq child-depth (+ (caddr parent-node) 1))
					(setq child-path (append temp-path (list 'left)))
					(cond
						((equal heur-option 'heuristic-1)
							(setq child-heur (similarity child-state))
						)
						((equal heur-option 'heuristic-2)
							(setq child-heur (manhattan-distances child-state))
						)
						((equal heur-option 'nil)
							(setq child-heur 0)
						)
					)
				)
			)
			((equal move-action 'right) 
				(progn
					(setq child-state (move-right child-state))
					(setq child-depth (+ (caddr parent-node) 1))
					(setq child-path (append temp-path (list 'right)))
					(cond
						((equal heur-option 'heuristic-1)
							(setq child-heur (similarity child-state))
						)
						((equal heur-option 'heuristic-2)
							(setq child-heur (manhattan-distances child-state))
						)
						((equal heur-option 'nil)
							(setq child-heur 0)
						)
					)
				)
			)
		)
		;(print parent-node)
		(setq child-node (list child-state child-heur child-depth child-path))
	)
)

(defun make-node-list (node)
	(list node)
)

(defun add-node-to-list (node node-list)
	(append (list node) node-list)
)

(defun remove-node-from-list (node-list)
	(cdr node-list)
)

(defun expand (node node-list heur-option)
	(let 
	((current-blank-pos) (moves-list) (child-node) (result-list '()))
		(if (atom node)
			nil
			(progn
				(setq current-blank-pos (get-pos-blank (car node)))
				(setq moves-list (possible-moves current-blank-pos))
				(dotimes (i (length moves-list) result-list)
					(setq child-node (generate-child-node node (nth i moves-list) heur-option))
					;(print child-node)
					(if (dupe (car child-node) node-list)
						nil
						(setq result-list (add-node-to-list child-node result-list))
					)
				)
			)
		)
		;(print result-list)
	)
)

(defun dfs-iter (initial_configuration heur-option)
	(let (cur-node node-list (goal-found nil) (node-list-max-length 0))
		(setq node-list (make-node-list (make-node initial_configuration 0 0 '())))
		(setq node-list-max-length (length node-list))
		(loop (unless (equal goal-found T))
			(if (< (length node-list) 1) (return-from dfs-iter nil))
			(if (< node-list-max-length (length node-list))
				(setq node-list-max-length (length node-list))
			)
			(setq cur-node (car node-list))
			(setq node-list (cdr node-list))
			(if (check-goal-state (car cur-node))
				(progn
					(format t "Solution Path: ~S~%Depth: ~D~%Max node-list length: ~D~%"
						(cadddr cur-node) (caddr cur-node) node-list-max-length)
					(return-from dfs-iter cur-node)
				)
				(setq node-list (append (expand cur-node node-list heur-option) node-list))
			)
		)
	)
)

(defun dfs (initial_configuration)
	(dfs-iter initial_configuration 'nil)
)

(defun greedy-iter (initial_configuration heuristic_function)
	(let (cur-node node-list (goal-found nil) (node-list-max-length 0))
		(setq node-list (make-node-list (make-node initial_configuration 0 0 '())))
		(setq node-list-max-length (length node-list))
		(loop (unless (equal goal-found T))
			(if (< (length node-list) 1) (return-from greedy-iter nil))
			(if (< node-list-max-length (length node-list))
				(setq node-list-max-length (length node-list))
			)
			(setq node-list (sort node-list #'nodes<))
			(setq cur-node (car node-list))
			(setq node-list (cdr node-list))
			(if (check-goal-state (car cur-node))
				(progn
					(format t "Solution Path: ~S~%Depth: ~D~%Max node-list length: ~D~%"
						(cadddr cur-node) (caddr cur-node) node-list-max-length)
					(return-from greedy-iter cur-node)
				)
				(setq node-list (append (expand cur-node node-list heuristic_function) node-list))
			)
		)
	)
)

(defun greedy (initial_configuration heuristic_function)
	; function body
	; implementation should work for both of the heuristic functions
	(greedy-iter initial_configuration heuristic_function)
)

;;; F(n) = g(n) + h(n) 
;;; g(n) = depth of node
;;; h(n) = heuristic function value

(defun a_star-iter (initial_configuration heuristic_function)
	(let (cur-node node-list (goal-found nil) (node-list-max-length 0))
		(setq node-list (make-node-list (make-node initial_configuration 0 0 '())))
		(setq node-list-max-length (length node-list))
		(loop (unless (equal goal-found T))
			(if (< (length node-list) 1) (return-from a_star-iter nil))
			(if (< node-list-max-length (length node-list))
				(setq node-list-max-length (length node-list))
			)
			(setq node-list (sort node-list #'nodes-a-star<))
			(setq cur-node (car node-list))
			(setq node-list (cdr node-list))
			(if (check-goal-state (car cur-node))
				(progn
					(format t "Solution Path: ~S~%Depth: ~D~%Max node-list length: ~D~%"
						(cadddr cur-node) (caddr cur-node) node-list-max-length)
					(return-from a_star-iter cur-node)
				)
				(setq node-list (append (expand cur-node node-list heuristic_function) node-list))
			)
		)
	)
)

(defun a_star (initial_configuration heuristic_function)
	; function body
	(a_star-iter initial_configuration heuristic_function)
)

