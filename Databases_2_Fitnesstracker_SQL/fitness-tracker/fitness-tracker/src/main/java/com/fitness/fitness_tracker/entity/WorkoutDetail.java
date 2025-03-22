package com.fitness.fitness_tracker.entity;

import jakarta.persistence.*;

@Entity
@Table(name = "\"Boehmisch_WorkoutDetails\"") // Genaue Übereinstimmung mit dem Tabellennamen
public class WorkoutDetail {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer workoutDetailID;

    @Column(nullable = false)
    private Integer workoutID;

    @Column(nullable = false)
    private Integer uebungID;

    @Column(nullable = false)
    private Integer satzNummer;

    @Column(nullable = false)
    private Double gewicht;

    @Column(nullable = false)
    private Integer wiederholungen;

    @Column(nullable = false)
    private Boolean completed;

    @Transient
    private String uebungName;

    public String getUebungName() {
        return uebungName;
    }

    public void setUebungName(String uebungName) {
        this.uebungName = uebungName;
    }

    // Getter und Setter
    public Integer getWorkoutDetailID() {
        return workoutDetailID;
    }

    public void setWorkoutDetailID(Integer workoutDetailID) {
        this.workoutDetailID = workoutDetailID;
    }

    public Integer getWorkoutID() {
        return workoutID;
    }

    public void setWorkoutID(Integer workoutID) {
        this.workoutID = workoutID;
    }

    public Integer getUebungID() {
        return uebungID;
    }

    public void setUebungID(Integer uebungID) {
        this.uebungID = uebungID;
    }

    public Integer getSatzNummer() {
        return satzNummer;
    }

    public void setSatzNummer(Integer satzNummer) {
        this.satzNummer = satzNummer;
    }

    public Double getGewicht() {
        return gewicht;
    }

    public void setGewicht(Double gewicht) {
        this.gewicht = gewicht;
    }

    public Integer getWiederholungen() {
        return wiederholungen;
    }

    public void setWiederholungen(Integer wiederholungen) {
        this.wiederholungen = wiederholungen;
    }

    public Boolean getCompleted() {
        return completed;
    }

    public void setCompleted(Boolean completed) {
        this.completed = completed;
    }
}
