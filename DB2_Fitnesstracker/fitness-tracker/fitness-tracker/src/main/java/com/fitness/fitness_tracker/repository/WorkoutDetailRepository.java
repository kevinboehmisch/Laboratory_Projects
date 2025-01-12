package com.fitness.fitness_tracker.repository;

import com.fitness.fitness_tracker.entity.WorkoutDetail;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface WorkoutDetailRepository extends JpaRepository<WorkoutDetail, Integer> {
    List<WorkoutDetail> findByWorkoutID(Integer workoutID); // Custom Query Method
}

