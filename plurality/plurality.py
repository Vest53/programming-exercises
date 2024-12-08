def plural_election():
    # Defining candidates
    candidates = []
    num_candidates = int(input("Enter the number of candidates: "))

    for i in range(num_candidates):
        name = input(f"Enter the name of candidate {i + 1}: ")
        candidates.append(name)

    # Initializing vote count
    votes = {candidate: 0 for candidate in candidates}

    # Capturing votes
    num_voters = int(input("Enter the number of voters: "))

    for i in range(num_voters):
        vote = input(f"Voter {i + 1}, vote for a candidate (enter the name): ")
        if vote in votes:
            votes[vote] += 1
        else:
            print("Candidate not found. Vote not counted.")

    # Determining the winner
    winner = max(votes, key=votes.get)
    vote_count = votes[winner]

    # Displaying results
    print("\nElection Results:")
    for candidate, count in votes.items():
        print(f"{candidate}: {count} votes")

    print(f"\nThe winner is: {winner} with {vote_count} votes.")

# Execute the function
plural_election()
