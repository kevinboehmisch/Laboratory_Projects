package com.fitness.fitness_tracker.repository;

import com.fitness.fitness_tracker.entity.Workout;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

@Repository
public interface WorkoutRepository extends JpaRepository<Workout, Integer> {

    @Query(value = "EXEC dbo.Boehmisch_GetAllWorkoutsWithDetails", nativeQuery = true)
    List<Object[]> getAllWorkoutsWithDetails();

}
