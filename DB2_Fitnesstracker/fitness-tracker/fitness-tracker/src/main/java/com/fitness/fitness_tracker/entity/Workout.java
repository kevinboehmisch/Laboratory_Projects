package com.fitness.fitness_tracker.entity;

import jakarta.persistence.*;
import java.util.List;

@Entity
@Table(name = "Boehmisch_Workouts")
public class Workout {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer workoutID;

    @Column(nullable = false)
    private String name;

    @Column
    private Integer gesamtdauer;

    @Transient // Dieses Feld wird nicht direkt in der Datenbank gespeichert
    private List<WorkoutDetail> details;

    // Getter und Setter
    public Integer getWorkoutID() {
        return workoutID;
    }

    public void setWorkoutID(Integer workoutID) {
        this.workoutID = workoutID;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getGesamtdauer() {
        return gesamtdauer;
    }

    public void setGesamtdauer(Integer gesamtdauer) {
        this.gesamtdauer = gesamtdauer;
    }

    public List<WorkoutDetail> getDetails() {
        return details;
    }

    public void setDetails(List<WorkoutDetail> details) {
        this.details = details;
    }
}
