package com.fitness.fitness_tracker.service;

import com.fitness.fitness_tracker.entity.WorkoutDetail;
import com.fitness.fitness_tracker.repository.WorkoutDetailRepository;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class WorkoutDetailService {

    private final WorkoutDetailRepository workoutDetailRepository;

    public WorkoutDetailService(WorkoutDetailRepository workoutDetailRepository) {
        this.workoutDetailRepository = workoutDetailRepository;
    }
    public List<WorkoutDetail> findByWorkoutID(Integer workoutID) {
        return workoutDetailRepository.findByWorkoutID(workoutID);
    }
    
    public List<WorkoutDetail> getAllWorkoutDetails() {
        return workoutDetailRepository.findAll();
    }
    public List<WorkoutDetail> saveWorkoutDetails(List<WorkoutDetail> details) {
        return workoutDetailRepository.saveAll(details);
    }
    public WorkoutDetail createWorkoutDetail(WorkoutDetail workoutDetail) {
        return workoutDetailRepository.save(workoutDetail);
    }
}
