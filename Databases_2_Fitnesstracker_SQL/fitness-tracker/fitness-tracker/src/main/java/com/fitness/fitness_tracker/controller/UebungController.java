package com.fitness.fitness_tracker.controller;


import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import com.fitness.fitness_tracker.entity.Uebung;
import com.fitness.fitness_tracker.service.UebungService;

import java.util.List;
import java.util.Map;



@RestController
@RequestMapping("/api/uebungen")
public class UebungController {

    private final UebungService uebungService;

    public UebungController(UebungService uebungService) {
        this.uebungService = uebungService;
    }

    // Alle Übungen abrufen
    @GetMapping
    public ResponseEntity<List<Uebung>> getAllUebungen() {
        return ResponseEntity.ok(uebungService.getAllUebungen());
    }

    // Neue Übung erstellen
    @PostMapping
    public ResponseEntity<Uebung> createUebung(@RequestBody Uebung uebung) {
        return ResponseEntity.ok(uebungService.createUebung(uebung));
    }

    @GetMapping("/averages")
    public ResponseEntity<List<Map<String, Object>>> getExercisesWithAverages() {
        try {
            List<Map<String, Object>> averages = uebungService.getExercisesWithAverages();
            return ResponseEntity.ok(averages);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
    
}
