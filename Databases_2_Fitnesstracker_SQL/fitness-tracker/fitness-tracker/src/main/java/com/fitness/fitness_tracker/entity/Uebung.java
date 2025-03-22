package com.fitness.fitness_tracker.entity;


import jakarta.persistence.*;

@Entity
@Table(name = "Boehmisch_Uebungen")
public class Uebung {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer uebungID;

    @Column(nullable = false, length = 100)
    private String name;

    @Column(length = 50)
    private String muskelgruppe;

    @Column(length = 500)
    private String beschreibung;

    // Getter und Setter
    public Integer getUebungID() {
        return uebungID;
    }

    public void setUebungID(Integer uebungID) {
        this.uebungID = uebungID;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getMuskelgruppe() {
        return muskelgruppe;
    }

    public void setMuskelgruppe(String muskelgruppe) {
        this.muskelgruppe = muskelgruppe;
    }

    public String getBeschreibung() {
        return beschreibung;
    }

    public void setBeschreibung(String beschreibung) {
        this.beschreibung = beschreibung;
    }
}
