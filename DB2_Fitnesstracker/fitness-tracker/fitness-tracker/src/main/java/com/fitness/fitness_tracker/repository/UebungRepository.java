package com.fitness.fitness_tracker.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.fitness.fitness_tracker.entity.Uebung;

public interface UebungRepository extends JpaRepository<Uebung, Long> {
}
