package com.jodel.jodel;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface VoteRepository extends JpaRepository<Vote, Long> {
    List<Vote> findByPostId(Long postId);
    Vote findByPostIdAndUserId(Long postId, String userId);
}