package com.fitness.fitness_tracker.service;

import com.fitness.fitness_tracker.entity.Workout;
import com.fitness.fitness_tracker.repository.WorkoutRepository;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Service
public class WorkoutService {

    private final WorkoutRepository workoutRepository;

    // Konstruktorinjektion
    public WorkoutService(WorkoutRepository workoutRepository) {
        this.workoutRepository = workoutRepository;
    }

    public List<Workout> getAllWorkouts() {
        return workoutRepository.findAll();
    }

    public Workout saveWorkout(Workout workout) {
        return workoutRepository.save(workout);
    }

    public List<Map<String, Object>> getAllWorkoutsWithDetails() {
        List<Object[]> results = workoutRepository.getAllWorkoutsWithDetails();
        List<Map<String, Object>> formattedResults = new ArrayList<>();

        for (Object[] row : results) {
            Map<String, Object> workout = new HashMap<>();
            workout.put("WorkoutID", row[0]);
            workout.put("WorkoutName", row[1]);
            workout.put("WorkoutDetailID", row[2]);
            workout.put("UebungID", row[3]);
            workout.put("UebungName", row[4]);
            workout.put("Muskelgruppe", row[5]);
            workout.put("SatzNummer", row[6]);
            workout.put("Gewicht", row[7]);
            workout.put("Wiederholungen", row[8]);
            workout.put("Completed", row[9]);

            formattedResults.add(workout);
        }

        return formattedResults;
    }
}
