(ns food
  (:require [clojure.string :as str]))

;; Ensures Map is valid
(defn isValidMap [mapLines]
  (let [line-lengths (map count mapLines)]
    (apply = line-lengths)))

(defn isInBounds [x y map]
  (and (>= x 0) (< x (count map))
       (>= y 0) (< y (count (first map)))))

(defn isOpen [x y map]
  (let [cell (get-in map [x y])]
    (or (= cell \-) (= cell \@))))

(defn markPath [map x y symbol]
  (assoc-in map [x y] symbol))

(defn findPath [map x y]
  (cond 
    (not (isInBounds x y map)) [false map]
    (= (get-in map [x y]) \@) [true map]
    (not (isOpen x y map)) [false map]
    :else
    (let [map (markPath map x y \+)
          directions [[0 -1] [1 0] [0 1] [-1 0]]]
      (loop [dirs directions
             map map]
        (if (empty? dirs)
          [false (markPath map x y \!)]
          (let [[dx dy] (first dirs)
                [found? new-map] (findPath map (+ x dx) (+ y dy))]
            (if found?
              [true new-map]
              (recur (rest dirs) new-map))))))))

(defn findFood [fileName]
  (let [mapContent (slurp fileName)
        mapLines (vec (map vec (str/split-lines mapContent)))]
    (if (isValidMap mapLines)
      (let [[found? result-map] (findPath mapLines 0 0)]
        (println "\nFido's Challenge:")
        (doseq [line result-map]
          (println (apply str line)))
        (if found?
          (println "Fido found the food!")
          (println "Fido couldn't find the food.")))
      (println "Invalid Map"))))