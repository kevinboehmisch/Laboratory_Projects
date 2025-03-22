package com.jodel.jodel;

import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/votes")
public class VoteController {

    private final VoteService voteService;

    public VoteController(VoteService voteService) {
        this.voteService = voteService;
    }

    @PostMapping("/{postId}/up")
    public Vote upvotePost(@PathVariable Long postId, @RequestParam String userId) {
        return voteService.addVote(postId, userId, VoteDirection.UP);
    }

    @PostMapping("/{postId}/down")
    public Vote downvotePost(@PathVariable Long postId, @RequestParam String userId) {
        return voteService.addVote(postId, userId, VoteDirection.DOWN);
    }

    @GetMapping("/{postId}/count")
    public int getVoteCount(@PathVariable Long postId) {
        return voteService.getVoteCount(postId);
    }
}