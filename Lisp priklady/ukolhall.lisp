;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;

#|
Před načtením souboru načtěte knihovnu micro-graphics
Pokud při načítání (kompilaci) dojde k chybě
"Reader cannot find package MG",
znamená to, že knihovna micro-graphics není načtená.
|#

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Třída point
;;;

(defclass point () 
  ((x :initform 0) 
   (y :initform 0)
   (color :initform :black) 
   (thickness :initform 1)))


;;; 
;;; Vlastnosti x, y, r, phi
;;;

(defmethod x ((point point))
  (slot-value point 'x))

(defmethod y ((point point))
  (slot-value point 'y))

(defmethod set-x ((point point) value)
  (unless (typep value 'number)
    (error "x coordinate of a point should be a number"))
  (setf (slot-value point 'x) value)
  point)

(defmethod set-y ((point point) value)
  (unless (typep value 'number)
    (error "y coordinate of a point should be a number"))
  (setf (slot-value point 'y) value)
  point)

(defmethod r ((point point)) 
  (let ((x (slot-value point 'x)) 
        (y (slot-value point 'y))) 
    (sqrt (+ (* x x) (* y y)))))

(defmethod phi ((point point)) 
  (phase (complex (slot-value point 'x)
                  (slot-value point 'y))))

(defmethod set-r-phi ((point point) r phi) 
  (let ((complex (* (cis phi) r)))
    (set-x point (realpart complex))
    (set-y point (imagpart complex)))
  point)

(defmethod set-r ((point point) value) 
  (set-r-phi point value (phi point)))

(defmethod set-phi ((point point) value) 
  (set-r-phi point (r point) value))


;;;
;;; Vlastnosti související s kreslením: color, thickness
;;;

(defmethod color ((pt point)) 
  (slot-value pt 'color)) 

(defmethod set-color ((pt point) value) 
  (setf (slot-value pt 'color) value)
  pt) 

(defmethod thickness ((pt point)) 
  (slot-value pt 'thickness)) 

(defmethod set-thickness ((pt point) value) 
  (setf (slot-value pt 'thickness) value)
  pt)

;;;
;;; Kreslení
;;;

;; U bodu kreslíme kruh s poloměrem rovným thickness

(defmethod set-mg-params ((pt point) mgw) 
  (mg:set-param mgw :foreground (color pt)) 
  (mg:set-param mgw :filledp t)
  pt)

(defmethod do-draw ((pt point) mgw) 
  (mg:draw-circle mgw 
                  (x pt) 
                  (y pt) 
                  (thickness pt))
  pt)

(defmethod draw ((pt point) mgw)
  (set-mg-params pt mgw)
  (do-draw pt mgw))


;;;
;;; Geometrické transformace
;;;

(defmethod move ((pt point) dx dy)
  (set-x pt (+ (x pt) dx))
  (set-y pt (+ (y pt) dy))
  pt)

(defmethod rotate ((pt point) angle center)
  (let ((cx (x center))
        (cy (y center)))
    (move pt (- cx) (- cy))
    (set-phi pt (+ (phi pt) angle))
    (move pt cx cy)
    pt))

(defmethod scale ((pt point) coeff center)
  (let ((cx (x center))
        (cy (y center)))
    (move pt (- cx) (- cy))
    (set-r pt (* (r pt) coeff))
    (move pt cx cy)
    pt))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Třída circle
;;;

(defclass circle () 
  ((center :initform (make-instance 'point)) 
   (radius :initform 1)
   (color :initform :black)
   (thickness :initform 1)
   (filledp :initform nil)))


;;;
;;; Základní vlastnosti
;;;

(defmethod radius ((c circle))
  (slot-value c 'radius))

(defmethod set-radius ((c circle) value)
  (when (< value 0)
    (error "Circle radius should be a non-negative number"))
  (setf (slot-value c 'radius) value)
  c)

(defmethod center ((c circle))
  (slot-value c 'center))


;;;
;;; Vlastnosti související s kreslením
;;;

(defmethod color ((c circle))
  (slot-value c 'color))

(defmethod set-color ((c circle) value)
  (setf (slot-value c 'color) value)
  c)

(defmethod thickness ((c circle))
  (slot-value c 'thickness))

(defmethod set-thickness ((c circle) value)
  (setf (slot-value c 'thickness) value)
  c)

(defmethod filledp ((c circle))
  (slot-value c 'filledp))

(defmethod set-filledp ((c circle) value)
  (setf (slot-value c 'filledp) value)
  c)


;;;
;;; Kreslení
;;;

(defmethod set-mg-params ((c circle) mgw)
  (mg:set-param mgw :foreground (color c))
  (mg:set-param mgw :thickness (thickness c))
  (mg:set-param mgw :filledp (filledp c))
  c)

(defmethod do-draw ((c circle) mg-window)
  (mg:draw-circle mg-window
                  (x (center c))
                  (y (center c))
                  (radius c))
  c)

(defmethod draw ((c circle) mg-window)
  (set-mg-params c mg-window)
  (do-draw c mg-window))


;;;
;;; Geometrické transformace
;;;

(defmethod move ((c circle) dx dy)
  (move (center c) dx dy)
  c)

(defmethod rotate ((c circle) angle center)
  (rotate (center c) angle center)
  c)

(defmethod scale ((c circle) coeff center)
  (scale (center c) coeff center)
  (set-radius c (* (radius c) coeff))
  c)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Třída picture
;;;

(defclass picture ()
  ((items :initform '())))


;;;
;;; Vlastnost items
;;;

(defmethod check-item ((pic picture) item)
  (unless (or (typep item 'point) 
              (typep item 'circle) 
              (typep item 'polygon)
              (typep item 'triangle)
              (typep item 'picture))
    (error "Invalid picture element type."))
  pic)

(defmethod check-items ((pic picture) items)
  (dolist (item items)
    (check-item pic item))
  pic)

(defmethod items ((pic picture)) 
  (copy-list (slot-value pic 'items)))

(defmethod set-items ((pic picture) value) 
  (check-items pic value)
  (setf (slot-value pic 'items) (copy-list value))
  pic)


;;;
;;; Kreslení
;;;

(defmethod draw ((pic picture) mg-window)
  (dolist (item (reverse (items pic)))
    (draw item mg-window))
  pic)


;;;
;;; Geometrické transformace
;;;

(defmethod move ((pic picture) dx dy)
  (dolist (item (items pic))
    (move item dx dy))
  pic)

(defmethod rotate ((pic picture) angle center)
  (dolist (item (items pic))
    (rotate item angle center))
  pic)

(defmethod scale ((pic picture) coeff center)
  (dolist (item (items pic))
    (scale item coeff center))
  pic)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Třída polygon
;;;

(defclass polygon ()
  ((items :initform '())
   (color :initform :black)
   (thickness :initform 1)
   (filledp :initform nil)
   (closedp :initform t)))


;;;
;;; Vlastnost items
;;;

(defmethod check-item ((poly polygon) item)
  (unless (typep item 'point) 
    (error "Items of polygon should be points."))
  poly)

(defmethod check-items ((poly polygon) items)
  (dolist (item items)
    (check-item poly item))
  poly)

(defmethod items ((poly polygon)) 
  (copy-list (slot-value poly 'items)))

(defmethod set-items ((poly polygon) value) 
  (check-items poly value)
  (setf (slot-value poly 'items) (copy-list value))
  poly)


;;;
;;; Vlastnosti pro kreslení
;;;

(defmethod color ((p polygon))
  (slot-value p 'color))

(defmethod set-color ((p polygon) value)
  (setf (slot-value p 'color) value)
  p)

(defmethod thickness ((p polygon))
  (slot-value p 'thickness))

(defmethod set-thickness ((p polygon) value)
  (setf (slot-value p 'thickness) value)
  p)

(defmethod closedp ((p polygon))
  (slot-value p 'closedp))

(defmethod set-closedp ((p polygon) value)
  (setf (slot-value p 'closedp) value)
  p)

(defmethod filledp ((p polygon))
  (slot-value p 'filledp))

(defmethod set-filledp ((p polygon) value)
  (setf (slot-value p 'filledp) value)
  p)


;;; 
;;; Kreslení
;;;

(defmethod set-mg-params ((poly polygon) mg-window) 
  (mg:set-param  mg-window :foreground (color poly)) 
  (mg:set-param  mg-window :thickness (thickness poly)) 
  (mg:set-param  mg-window :filledp (filledp poly))
  (mg:set-param  mg-window :closedp (closedp poly))
  poly)

(defmethod polygon-coordinates ((p polygon))
  (let (coordinates)
    (dolist (point (reverse (items p)))
      (setf coordinates (cons (y point) coordinates)
            coordinates (cons (x point) coordinates)))
    coordinates))

(defmethod do-draw ((poly polygon) mg-window) 
  (mg:draw-polygon mg-window 
                   (polygon-coordinates poly))
  poly)

(defmethod draw ((poly polygon) mg-window) 
  (set-mg-params poly mg-window) 
  (do-draw poly mg-window))


;;;
;;; Geometrické transformace
;;;

(defmethod move ((poly polygon) dx dy)
  (dolist (item (items poly))
    (move item dx dy))
  poly)

(defmethod rotate ((poly polygon) angle center)
  (dolist (item (items poly))
    (rotate item angle center))
  poly)

(defmethod scale ((poly polygon) coeff center)
  (dolist (item (items poly))
    (scale item coeff center))
  poly)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Třída window
;;;

(defclass window ()
  ((mg-window :initform (mg:display-window))
   (shape :initform nil)
   (background :initform :white)))


;;;
;;; Vlastnosti
;;;

(defmethod shape ((w window))
  (slot-value w 'shape))

(defmethod set-shape ((w window) shape)
  (setf (slot-value w 'shape) shape)
  w)

(defmethod background ((w window))
  (slot-value w 'background))

(defmethod set-background ((w window) color)
  (setf (slot-value w 'background) color)
  w)


;;;
;;; Vykreslování
;;;

(defmethod redraw ((window window))
  (let ((mgw (slot-value window 'mg-window)))
    (mg:set-param mgw :background (background window))
    (mg:clear mgw)
    (when (shape window)
      (draw (shape window) mgw)))
  window)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;ukol trochu



;(defun make-green-object ()
 ;              (let ((p (make-instance 'polygon)))
  ;               (set-items
   ;               (set-color (set-thickness p 5) :green)
    ;              (list (move (make-instance 'point) 50 100)
     ;                   (move (make-instance 'point) 150 100)
      ;                  (move (make-instance 'point) 150 200)
       ;                 (move (make-instance 'point) 50 200)))))

;circle 100 100 a radius 50

(defun make-ghost-body (color)
  (let ((b (make-instance 'polygon)))
    (set-items
     (set-color (set-filledp b t) color)
     (list (move (make-instance 'point) 0 75)
           (move (make-instance 'point) 150 75)
           (move (make-instance 'point) 150 175)
           (move (make-instance 'point) 0 175)))))

(defun make-ghost-head (color)
  (let ((h (make-instance 'circle)))
    (set-x (center h) 75)
    (set-y (center h) 75)
    (set-radius h 75)
    (set-color h color)
    (set-filledp h t)
    h))

(defun make-ghost-triangle (x1 y1 x2 y2 x3 y3 color)
  (let ((tr (make-instance 'triangle)))
    (set-vertex-a tr (move (vertex-a tr) x1 y1))
    (set-vertex-b tr (move (vertex-b tr) x2 y2))
    (set-vertex-c tr (move (vertex-c tr) x3 y3))
    (set-color tr color)
    (set-filledp tr t)
    tr))

(defun make-ghost-eye(x1 y1 rad color)
  (let ((e (make-instance 'circle)))
    (set-x (center e) x1)
    (set-y (center e) y1)
    (set-radius e rad)
    (set-color e color)
    (set-filledp e t)
    e))

(defun make-ghost (color)
  (let ((ghost (make-instance 'picture)))
    (set-items ghost 
               (list
                (make-ghost-eye 55 75 5 ':black)
                (make-ghost-eye 50 75 17 ':white)
                (make-ghost-eye 105 75 5 ':black)
                (make-ghost-eye 100 75 17 ':white)
                (make-ghost-head color)
                (make-ghost-body color)
                (make-ghost-triangle 0 175 0 200 25 175 color)
                (make-ghost-triangle 25 175 50 200 75 175 color)
                (make-ghost-triangle 75 175 100 200 125 175 color)
                (make-ghost-triangle 125 175 150 200 150 175 color)))
    (move ghost -75 -100)
    ghost))

(defun display-halloween-window (gc)
  (let ((wind (make-instance 'window)))
    (set-background wind :black)
    (dotimes (x gc) 
      (set-shape wind (move (make-ghost :red) 150 150)))
    wind))
  

;0 175))
  ;  ( 0 200))
   ;  25 175))

;setf c3 (make-ghost-triangle 25 175 50 200 75 175))


;(setf c4 (make-ghost-triangle 75 175 100 200 125 175))


;setf c5 (make-ghost-triangle 125 175 150 200 150 175))
;;;;;;;;Trida triagle;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




(defclass triangle ()
  ((vertex-a :initform (make-instance 'point))
   (vertex-b :initform (make-instance 'point))
   (vertex-c :initform (make-instance 'point))
   (color :initform :black)
   (thickness :initform 1)
   (filledp :initform nil)
   (closedp :initform t)))

(defmethod vertex-a ((triangle triangle))
  (slot-value triangle 'vertex-a))

(defmethod vertex-b ((triangle triangle))
  (slot-value triangle 'vertex-b))

(defmethod vertex-c ((triangle triangle))
  (slot-value triangle 'vertex-c))



(defmethod set-vertex-a ((triangle triangle) value)
  (if (typep value 'point)
      (setf (slot-value triangle 'vertex-a) value)
    (error "Vertex a is not point")))

(defmethod set-vertex-b ((triangle triangle) value)
  (if (typep value 'point)
      (setf (slot-value triangle 'vertex-b) value)
    (error "Vertex b is not point")))

(defmethod set-vertex-c ((triangle triangle) value)
  (if (typep value 'point)
      (setf (slot-value triangle 'vertex-c) value)
    (error "Vertex c is not point")))


(defmethod vertices ((triangle triangle))
  (list (slot-value triangle 'vertex-a)
        (slot-value triangle 'vertex-b)
        (slot-value triangle 'vertex-c)))






(defmethod color ((tr triangle))
  (slot-value tr 'color))

(defmethod set-color ((tr triangle) value)
  (setf (slot-value tr 'color) value)
  tr)

(defmethod thickness ((tr triangle))
  (slot-value tr 'thickness))

(defmethod set-thickness ((tr triangle) value)
  (setf (slot-value tr 'thickness) value)
  tr)

(defmethod closedp ((tr triangle))
  (slot-value tr 'closedp))

(defmethod set-closedp ((tr triangle) value)
  (setf (slot-value tr 'closedp) value)
  tr)

(defmethod filledp ((tr triangle))
  (slot-value tr 'filledp))

(defmethod set-filledp ((tr triangle) value)
  (setf (slot-value tr 'filledp) value)
  tr)


(defmethod move ((tr triangle) dx dy)
  (set-x (vertex-a tr) (+ (x (vertex-a tr)) dx))
  (set-y (vertex-a tr) (+ (y (vertex-a tr)) dy))
  (set-x (vertex-b tr) (+ (x (vertex-b tr)) dx))
  (set-y (vertex-b tr) (+ (y (vertex-b tr)) dy))
  (set-x (vertex-c tr) (+ (x (vertex-c tr)) dx))
  (set-y (vertex-c tr) (+ (y (vertex-c tr)) dy)))
                
                

;;; 
;;; Kreslení
;;;

(defmethod set-mg-params ((tr triangle) mg-window) 
  (mg:set-param  mg-window :foreground (color tr)) 
  (mg:set-param  mg-window :thickness (thickness tr)) 
  (mg:set-param  mg-window :filledp (filledp tr))
  (mg:set-param  mg-window :closedp (closedp tr))
  tr)

(defmethod triangle-coordinates ((tr triangle))
  (let (coordinates)
    (dolist (point (vertices tr))
      (setf coordinates (cons (y point) coordinates)
            coordinates (cons (x point) coordinates)))
    coordinates))

(defmethod do-draw ((tr triangle) mg-window) 
  (mg:draw-polygon mg-window 
                   (triangle-coordinates tr))
  tr)

(defmethod draw ((tr triangle) mg-window) 
  (set-mg-params tr mg-window) 
  (do-draw tr mg-window))
