package com.fitness.fitness_tracker.controller;

import com.fitness.fitness_tracker.entity.Workout;
import com.fitness.fitness_tracker.service.WorkoutService;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/workouts")
public class WorkoutController {

    private final WorkoutService workoutService;

    // Konstruktorinjektion
    public WorkoutController(WorkoutService workoutService) {
        this.workoutService = workoutService;
    }

    // GET: Alle Workouts abrufen
    @GetMapping
    public ResponseEntity<List<Workout>> getAllWorkouts() {
        return new ResponseEntity<>(workoutService.getAllWorkouts(), HttpStatus.OK);
    }

    // POST: Neues Workout erstellen
    @PostMapping
    public ResponseEntity<Workout> createWorkout(@RequestBody Workout workout) {
        return new ResponseEntity<>(workoutService.saveWorkout(workout), HttpStatus.CREATED);
    }
}
