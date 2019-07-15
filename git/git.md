# git
## fork와 clone
### fork
- 다른 사람의 Github repository에서 내가 어떤 부분을 수정하거나 추가 기능을 넣고 싶을 때, 해당 repository를 내 Github repository로 그대로 복제하는 기능이다.
- fork한 저장소는 원본과 연결되어 있으며, 원본에 어떤 변화가 생기면 그대로 forked된 저장소로 반영할 수 있다. 이 때 fetch나 rebase의 과정이 필요하다.
- 원본 저장소에 변경사항을 적용하고 싶은 경우, 해당 저장소에 pull request를 해야 한다. 원본 저장소의 관리자로부터 승인될 경우, commit 및 merge되어 원본에 반영된다.

### clone
- clone은 특정 repository를 내 local machine에 복사하여 새로운 저장소를 만든다.
- 원본 저장소를 remote 저장소 origin으로 가지고 있다. 권한이 없는 경우 해당 저장소로 push하지 못한다.
- 기존의 원본 저장소와 연결되지 못하며, 그 저장소의 commit 등 로그를 보지 못한다.

## branch
### 브랜치 만들기
- branch <branchname>으로 브랜치를 생성할 수 있다.
- branch 명령만 입력 시 브랜치 목록 전체를 볼 수 있다.

### 브랜치 전환
- checkout <branch>로 사용할 브랜치를 명시적으로 지정할 수 있다.
- checkout -b <branch> 처럼 -b 옵션을 넣으면 브랜치 작성과 체크아웃을 한꺼번에 실행할 수 있다.