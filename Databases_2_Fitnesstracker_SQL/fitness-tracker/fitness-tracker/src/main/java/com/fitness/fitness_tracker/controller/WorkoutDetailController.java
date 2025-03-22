package com.fitness.fitness_tracker.controller;

import com.fitness.fitness_tracker.entity.WorkoutDetail;
import com.fitness.fitness_tracker.service.WorkoutDetailService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/workoutDetails")
public class WorkoutDetailController {

    private final WorkoutDetailService workoutDetailService;

    public WorkoutDetailController(WorkoutDetailService workoutDetailService) {
        this.workoutDetailService = workoutDetailService;
    }

    @GetMapping("/{workoutID}")
public ResponseEntity<List<WorkoutDetail>> getWorkoutDetailsByWorkoutID(@PathVariable Integer workoutID) {
    List<WorkoutDetail> workoutDetails = workoutDetailService.findByWorkoutID(workoutID);
    return ResponseEntity.ok(workoutDetails);
}

    // GET: Alle WorkoutDetails abrufen
    @GetMapping
    public ResponseEntity<List<WorkoutDetail>> getAllWorkoutDetails() {
        List<WorkoutDetail> workoutDetails = workoutDetailService.getAllWorkoutDetails();
        return ResponseEntity.ok(workoutDetails);
    }

    // POST: Neues WorkoutDetail erstellen
    @PostMapping
    public ResponseEntity<WorkoutDetail> createWorkoutDetail(@RequestBody WorkoutDetail workoutDetail) {
        WorkoutDetail createdDetail = workoutDetailService.createWorkoutDetail(workoutDetail);
        return ResponseEntity.ok(createdDetail);
    }
    // POST: Mehrere Neue WorkoutDetail erstellen
    @PostMapping("/batch")
    public ResponseEntity<List<WorkoutDetail>> createWorkoutDetails(@RequestBody List<WorkoutDetail> details) {
        List<WorkoutDetail> savedDetails = workoutDetailService.saveWorkoutDetails(details);
        return ResponseEntity.ok(savedDetails);
    }
}
