package com.fitness.fitness_tracker.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import com.fitness.fitness_tracker.entity.Uebung;

public interface UebungRepository extends JpaRepository<Uebung, Integer> {
        @Query(value = "EXEC dbo.Boehmisch_GetExercisesWithAverages", nativeQuery = true)
    List<Object[]> getExercisesWithAverages();
}
