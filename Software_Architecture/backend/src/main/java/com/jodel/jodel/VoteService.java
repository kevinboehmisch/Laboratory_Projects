package com.jodel.jodel;

import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class VoteService {

    private final VoteRepository voteRepository;
    private final PostRepository postRepository;

    public VoteService(VoteRepository voteRepository, PostRepository postRepository) {
        this.voteRepository = voteRepository;
        this.postRepository = postRepository;
    }

    public Vote addVote(Long postId, String userId, VoteDirection direction) {
        Post post = postRepository.findById(postId).orElseThrow(() -> new RuntimeException("Post not found"));
        Vote existingVote = voteRepository.findByPostIdAndUserId(postId, userId);

        if (existingVote != null) {
            existingVote.setDirection(direction);
            return voteRepository.save(existingVote);
        }

        Vote newVote = new Vote();
        newVote.setUserId(userId);
        newVote.setPost(post);
        newVote.setDirection(direction);
        return voteRepository.save(newVote);
    }

    public int getVoteCount(Long postId) {
        List<Vote> votes = voteRepository.findByPostId(postId);
        int upCount = (int) votes.stream().filter(v -> v.getDirection() == VoteDirection.UP).count();
        int downCount = (int) votes.stream().filter(v -> v.getDirection() == VoteDirection.DOWN).count();
        return upCount - downCount;
    }
}