import git
import os.path
import sys

REPO_PATH = sys.argv[1]

repo = git.Repo.init(REPO_PATH)
git = repo.git
curr_branch = repo.active_branch.name

sha = repo.head.object.hexsha
short_sha = repo.git.rev_parse(sha, short=7)

def get_branch_commit_num():
    curr_commit = repo.head.commit
    commits = list(repo.iter_commits(curr_branch))

    for i in range(0, len(commits)):
        if commits[i].hexsha == curr_commit.hexsha:
            return len(commits) - i

    print('Failed to find current commit')
    return -1

