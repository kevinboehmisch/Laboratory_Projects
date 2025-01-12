package com.fitness.fitness_tracker.controller;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import com.fitness.fitness_tracker.entity.Uebung;
import com.fitness.fitness_tracker.service.UebungService;

import java.util.List;



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
}
