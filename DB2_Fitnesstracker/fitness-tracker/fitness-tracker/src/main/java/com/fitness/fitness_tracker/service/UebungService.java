package com.fitness.fitness_tracker.service;

import org.springframework.stereotype.Service;

import com.fitness.fitness_tracker.entity.Uebung;
import com.fitness.fitness_tracker.repository.UebungRepository;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

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

    // Durchschnittliches Gewicht und Wiederholung pro Übung
    public List<Map<String, Object>> getExercisesWithAverages() {
        List<Object[]> results = uebungRepository.getExercisesWithAverages();
        List<Map<String, Object>> formattedResults = new ArrayList<>();

        for (Object[] row : results) {
            Map<String, Object> map = new HashMap<>();
            map.put("UebungID", row[0]);
            map.put("UebungName", row[1]);
            map.put("Muskelgruppe", row[2]);
            map.put("Beschreibung", row[3]);
            map.put("DurchschnittlicheWiederholungen", row[4]);
            map.put("DurchschnittlichesGewicht", row[5]);
            formattedResults.add(map);
        }

        return formattedResults;
    }
}
