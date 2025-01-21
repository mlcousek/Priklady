;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Třída triangle
;;;

(defclass triangle (abstract-polygon)
  ())

(defmethod initialize-instance ((tr triangle) &key)
  (call-next-method)
  (do-set-items tr (list (move (make-instance 'point) 0 -1)
                         (move (make-instance 'point) 1 1)
                         (move (make-instance 'point) -1 1))))

(defmethod vertex-a ((tr triangle))
  (first (items tr)))

(defmethod vertex-b ((tr triangle))
  (second (items tr)))

(defmethod vertex-c ((tr triangle))
  (third (items tr)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Třída spinner
;;;

(defclass spinner (compound-shape)
  ((items :initform '())
   (spinner-value :initform 0)
   (max-spinner-value :initform 10)
   (min-spinner-value :initform -10)
   (spinner-step :initform 1)
   (text-visible-p :initform t)))

;kresleni
(defmethod draw ((spinner spinner) mg-window)
  (dolist (item (items spinner))
    (if (eql item (spinner-text spinner))
        (when (text-visible-p spinner)
          (draw item mg-window))
      (draw item mg-window)))
  spinner)

;klikani
(defmethod solidp ((spinner spinner))
  nil)

(defmethod solid-subshapes ((spinner spinner))
  (mapcan 'solid-shapes (items spinner)))

(defmethod contains-point-p ((spinner spinner) point)
  (find-if (lambda (item)
	     (contains-point-p item point))
	   (items spinner)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;sv
(defmethod spinner-value ((spinner spinner)) 
  (slot-value spinner 'spinner-value))

(defmethod do-set-spinner-value ((spinner spinner) value)
  (setf (slot-value spinner 'spinner-value) value))

(defmethod set-spinner-value ((spinner spinner) value)
  (send-with-change spinner 'do-set-spinner-value value)
  (update-spinner-text spinner)
  spinner)

;maxsv
(defmethod max-spinner-value ((spinner spinner)) 
  (slot-value spinner 'max-spinner-value))

(defmethod do-set-max-spinner-value ((spinner spinner) value)
  (setf (slot-value spinner 'max-spinner-value) value)
  (if (< value (spinner-value spinner))
      (set-spinner-value spinner value)))

(defmethod set-max-spinner-value ((spinner spinner) value)
  (unless (numberp value)
    (error "Max spinner value by měla být číslo"))
  (if (< value (min-spinner-value spinner))
      (error "Max spinner value by měla být větší než min spinner value."))
  (send-with-change spinner 'do-set-max-spinner-value value))
;minsv
(defmethod min-spinner-value ((spinner spinner)) 
  (slot-value spinner 'min-spinner-value))

(defmethod do-set-min-spinner-value ((spinner spinner) value)
  (setf (slot-value spinner 'min-spinner-value) value)
  (if (> value (spinner-value spinner))
      (set-spinner-value spinner value)))
      
(defmethod set-min-spinner-value ((spinner spinner) value)
  (unless (numberp value)
    (error "Min spinner value by měla být číslo"))
  (if (> value (max-spinner-value spinner))
      (error "Min spinner value by měla být menší než max spinner value."))
  (send-with-change spinner 'do-set-min-spinner-value value))
;sps
(defmethod spinner-step ((spinner spinner))
  (slot-value spinner 'spinner-step))

(defmethod set-spinner-step ((spinner spinner) value)
  (unless (numberp value)
    (error "Spinner step by měl být číslo"))
  (setf (slot-value spinner 'spinner-step) value)
  spinner)
;tvp
(defmethod text-visible-p ((spinner spinner)) 
  (slot-value spinner 'text-visible-p))

(defmethod do-set-text-visible-p ((spinner spinner) value)
  (setf (slot-value spinner 'text-visible-p) value))

(defmethod set-text-visible-p ((spinner spinner) value) 
  (send-with-change spinner 'do-set-text-visible-p value))

;spinner items - funkce

(defmethod spinner-upper-arrow ((spinner spinner))
  (second (items spinner)))

(defmethod spinner-downer-arrow ((spinner spinner))
  (third (items spinner)))

(defmethod spinner-text ((spinner spinner))
  (first (items spinner)))

(defmethod update-spinner-text ((spinner spinner))
  (set-text (spinner-text spinner) 
            (format nil "~a" (spinner-value spinner))))

(defun spinner-items (spinner-value)
  (let ((upper-arr (make-triangle))
        (downer-arr (rotate (make-triangle) pi (make-instance 'point)))
        (text (set-text (make-instance 'text-shape)
                        (format nil "~a" spinner-value))))
    (list (move text 27 30)
          (move upper-arr 15 15)
          (move downer-arr 15 35))))

(defun make-triangle ()
  (scale (set-filledp (make-instance 'triangle) t)
         9
         (make-instance 'point)))

;ii
(defmethod initialize-instance ((spinner spinner) &key)
  (call-next-method)
  (do-set-items spinner (spinner-items (spinner-value spinner)))
  (add-event (spinner-upper-arrow spinner) 'ev-mouse-down 'ev-mouse-down-u)
  (add-event (spinner-downer-arrow spinner) 'ev-mouse-down 'ev-mouse-down-d)
  spinner)

;eventy
(defmethod ev-mouse-down-u ((spinner spinner) sender clicked button position)
  (when (eql button :left)
    (inc-spinner-value spinner))
  (send-event spinner 'ev-mouse-down clicked button position))


(defmethod ev-mouse-down-d ((spinner spinner) sender clicked button position)
  (when (eql button :left)
    (dec-spinner-value spinner))
  (send-event spinner 'ev-mouse-down clicked button position))

;;inc a dec value

(defmethod inc-spinner-value ((spinner spinner))
  (let ((new-value (+ (spinner-value spinner) (spinner-step spinner)))
        (max-value (max-spinner-value spinner)))
     (cond ((or (= new-value max-value) (> new-value max-value)) (set-spinner-value spinner max-value))        
           ((< new-value max-value) (set-spinner-value spinner new-value))))
  spinner)

(defmethod dec-spinner-value ((spinner spinner))
  (let ((new-value (- (spinner-value spinner) (spinner-step spinner)))
        (min-value (min-spinner-value spinner)))
     (cond ((or (= new-value min-value) (< new-value min-value)) (set-spinner-value spinner min-value))
            ((> new-value min-value) (set-spinner-value spinner new-value))))
  spinner)

#|
(setf w (make-instance 'window))
(setf s (make-instance 'spinner))
(set-shape w s)
(set-spinner-step s 12)
|#

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Třída spinner-picture
;;;

(defclass spinner-picture (abstract-picture)
  ((clicked-circle :initform nil)))
   
;cc
(defmethod clicked-circle ((sp spinner-picture)) 
  (slot-value sp 'clicked-circle))

(defmethod do-set-clicked-circle ((sp spinner-picture) value)
  (setf (slot-value sp 'clicked-circle) value))

;ii
(defmethod initialize-instance ((sp spinner-picture) &key)
  (call-next-method)
  (do-set-items sp (three-spinners-and-picture))
  (set-max-spinner-val-to-all-spinners sp 1000)  
  sp)

(defun three-spinners-and-picture ()
  (list (move (make-instance 'spinner) 0 0)
        (move (make-instance 'spinner) 60 0)
        (move (make-instance 'spinner) 120 0)
        (make-instance 'picture)))

;;;;;;;;;

(defmethod x-coordinate-spinner ((sp spinner-picture))
  (first (items sp)))

(defmethod y-coordinate-spinner ((sp spinner-picture))
  (second (items sp)))

(defmethod radius-spinner ((sp spinner-picture))
  (third (items sp)))

(defmethod picture ((sp spinner-picture))
  (fourth (items sp)))

(defmethod circles ((sp spinner-picture))
  (items (picture sp)))

(defmethod set-circles ((sp spinner-picture) value)
  (set-items (picture sp) value))

(defmethod ev-mouse-down ((sp spinner-picture) sender origin button position)
  (call-next-method)
  (when (typep origin 'circle)
    (do-set-clicked-circle sp origin))
  (when (clicked-circle sp) 
    (cond ((eql (spinner-downer-arrow (x-coordinate-spinner sp)) origin) (move (clicked-circle sp) (* (spinner-step (x-coordinate-spinner sp)) -1) 0))
          ((eql (spinner-upper-arrow (x-coordinate-spinner sp)) origin) (move (clicked-circle sp) (spinner-step (x-coordinate-spinner sp)) 0))
          ((eql (spinner-downer-arrow (y-coordinate-spinner sp)) origin) (move (clicked-circle sp) 0 (* (spinner-step (y-coordinate-spinner sp)) -1)))
          ((eql (spinner-upper-arrow (y-coordinate-spinner sp)) origin) (move (clicked-circle sp) 0 (spinner-step (y-coordinate-spinner sp))))
          ((eql (spinner-downer-arrow (radius-spinner sp)) origin) (set-radius (clicked-circle sp) (- (radius (clicked-circle sp)) (spinner-step (radius-spinner sp)))))
          ((eql (spinner-upper-arrow (radius-spinner sp)) origin) (set-radius (clicked-circle sp) (+ (spinner-step (radius-spinner sp)) (radius (clicked-circle sp))))))
    (update-spinners sp (clicked-circle sp))))

(defun set-max-spinner-val-to-all-spinners (spinner-picture val)
  (mapcar #'set-max-spinner-value (append (list (x-coordinate-spinner spinner-picture))
                                          (list (y-coordinate-spinner spinner-picture))
                                          (list (radius-spinner spinner-picture))) 
          (list val val val)))

(defmethod update-spinners ((sp spinner-picture) circle) 
  (update-spinner sp (x-coordinate-spinner sp) (x (center circle)))
  (update-spinner sp (y-coordinate-spinner sp) (y (center circle)))
  (update-spinner sp (radius-spinner sp) (radius circle)))

(defmethod update-spinner ((sp spinner-picture) spinner value)
  (when (< (max-spinner-value spinner) value)
      (set-max-spinner-value spinner value))
  (set-spinner-value spinner value))

#|
(setf sp (make-instance 'spinner-picture))
(set-circles sp (list (move (set-color (set-filledp (set-radius (make-instance 'circle) 25) t) :gold) 50 100)
                              (set-filledp (set-items (make-instance 'polygon) (list (move (make-instance 'point) 50 100)
                                                                                     (move (make-instance 'point) 50 170)
                                                                                     (move (make-instance 'point) 100 170))) t)
                              (move (set-color (set-filledp (set-radius (make-instance 'circle) 25) t) :blue) 120 100)
                              (move (set-color (set-filledp (set-radius (make-instance 'circle) 25) t) :red) 50 170)))                                               
(setf w (make-instance 'window))
(set-shape w sp)
(set-spinner-step (x-coordinate-spinner sp) 12)
|#