package com.fitness.fitness_tracker.service;

import org.springframework.stereotype.Service;

import com.fitness.fitness_tracker.entity.Uebung;
import com.fitness.fitness_tracker.repository.UebungRepository;

import java.util.List;

@Service
public class UebungService {

    private final UebungRepository uebungRepository;

    public UebungService(UebungRepository uebungRepository) {
        this.uebungRepository = uebungRepository;
    }

    // Alle Übungen abrufen
    public List<Uebung> getAllUebungen() {
        return uebungRepository.findAll();
    }

    // Neue Übung erstellen
    public Uebung createUebung(Uebung uebung) {
        return uebungRepository.save(uebung);
    }
}
