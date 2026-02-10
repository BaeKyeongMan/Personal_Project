#include "Avoid_Game.h"

int main()
{
	char input = 0;
	ObjPositions object = {
		.player = {2, 2},
		.monster = {27, 13}
	};
	StageInfo stageinfo = { 1, MAPSIZE, 20, 0 };
	char uiMessage[50] = "";
	char STAGE[MAPSIZE][MAPSIZE * 2]; // 맵 사이즈


	// 룰에 대한 설명
	GameRule(input);

	while (1)
	{
		// 만약 몬스터가 플레이어를 따라잡거나 Q를 누르면 종료
		if (GameOver(object, &stageinfo, input))
		{
			break;
		}

		// 맵 초기화
		Init_Map(STAGE, stageinfo.stageMapSize);

		// 위치 업데이트
		PositionUpdate(STAGE, &object);

		//맵 프린트
		PrintMap(STAGE, stageinfo.stageMapSize);

		// 메세지 프린트
		PrintMessage(&stageinfo, uiMessage);

		// 입력 받기
		input = _getch(); // Enter 없이 바로 키 입력 받기

		// 입력할 때 마다 무브 카운트 증가
		IsMoveKey(input, uiMessage, &stageinfo);

		// 스킬 사용 조건
		UsingSkill(input, &object, &stageinfo);

		// 플레이어 움직임
		MovePlayer(&object, input, STAGE);

		// 몬스터 이동
		MoveMonster(&object, input, STAGE);

		// 클리어 표시
		ClearStage(&stageinfo, &object);

		// 스테이지별 이동 횟수
		NextStage(&stageinfo);
	}

	// 게임 종료시 무브 카운트 (Q를 눌러서 종료했을 때도 포함)
	MoveCountPrint(input, object, &stageinfo);

	return 0;
}