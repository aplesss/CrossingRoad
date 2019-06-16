#include "CLine.h"
Line::Line()
{
	width = BOARD_GAME_RIGHT - BOARD_GAME_LEFT + 1;
}

Line::Line(COORD coord, vector<Object*> v, Direction thedir, short SleepTime, short SoundWaiting)
{
	obj = v;
	pos = coord;
	dir = thedir;
	height = obj[0]->Height() + 1;
	width = BOARD_GAME_RIGHT - BOARD_GAME_LEFT + 1;
	sleep = SleepTime;
	timeCount = 0;
	soundWaiting = SoundWaiting;

	if (v[0]->GetShape() != DINOSAURS && v[0]->GetShape() != BIRDS)
		stop = new StopLight(SleepTime, rand() % 2);
	else
		stop = nullptr;
}


int Line::Height()
{
	return height;
}

void Line::PosUpdate()
{
	int n = obj.size();

	if (stop != nullptr)
	{
		stop->UpdateTime();		 

		if (stop->IsRed())return;
	}
	for_each(obj.begin(), obj.end(), mem_fun(&Object::Move));
}

void Line::Draw()
{
	int n = obj.size();

	if (dir == DRIGHT) {
		if (stop != nullptr)
			stop->Draw(this->pos.X, this->pos.Y);
		for (int i = 1; i < n; i++) {

			const short obj_left = obj[i]->GetPos().X;
			const short obj_right = obj[i]->GetPos().X + obj[i]->Width() - 1;
			if (BOARD_GAME_RIGHT > obj_left && BOARD_GAME_RIGHT < obj_right) {

				obj[0]->SetPos(BOARD_GAME_LEFT - (BOARD_GAME_RIGHT - obj_left), obj[1]->GetPos().Y);
				for_each(obj.begin(), obj.end(), mem_fn(&Object::Draw));
				return;
			}
		}

		obj[0]->SetPos(0, 0);
		for_each(obj.begin() + 1, obj.end(), mem_fn(&Object::Draw));
	}
	else {
		if (stop != nullptr)
		{
			stop->Draw(this->pos.X + width - 3, this->pos.Y);
		}
		for (int i = 1; i < n; i++) {

			const short obj_left = obj[i]->GetPos().X;
			const short obj_right = obj[i]->GetPos().X + obj[i]->Width() - 1;

			if (BOARD_GAME_LEFT > obj_left && BOARD_GAME_LEFT < obj_right) {

				obj[0]->SetPos(BOARD_GAME_RIGHT - (BOARD_GAME_LEFT - obj_left), obj[1]->GetPos().Y);
				for_each(obj.begin(), obj.end(), mem_fn(&Object::Draw));

				return;
			}
		}

		obj[0]->SetPos(0, 0);
		for_each(obj.begin() + 1, obj.end(), mem_fn(&Object::Draw));
	}
}

void Line::Music(const People &people)
{
	if (IsInside(people) == false)
		return;

	if ((stop != nullptr && !stop->IsRed() && (obj[0]->GetShape() == CARS || obj[0]->GetShape() == TRUCKS))
		|| obj[0]->GetShape() == BIRDS || obj[0]->GetShape() == DINOSAURS)
	{
		if (timeCount % soundWaiting == 0)
		{
			timeCount = 0;
			obj[0]->Music();
		}

		timeCount += sleep;
	}
}

COORD Line::GetPos()
{
	return pos;
}

bool Line::IsImpact(People& people)
{
	int n = obj.size();
	const short people_left = people.GetPos().X;
	const short people_right = people.GetPos().X + people.Width() - 1;

	for (int i = 0; i < n; i++) {

		const int min_x = obj[i]->GetPos().X;
		const int max_x = obj[i]->GetPos().X + obj[i]->Width() - 1;

		if (people_left >= min_x && people_left <= max_x) {
			return true;
		}

		if (people_right >= min_x && people_right <= max_x) {
			return true;
		}
	}

	return false;
}

void Line::Write(ostream& outDev)
{
	int num;
	Objects type = obj[0]->GetShape();

	outDev.write((char*)&type, sizeof(type));
	outDev.write((char*)&width, sizeof(width));
	outDev.write((char*)&height, sizeof(height));
	outDev.write((char*)&pos, sizeof(pos));
	num = obj.size();

	outDev.write((char*)&num, sizeof(num));
	if (type == CARS || type == TRUCKS) {
		outDev.write((char*)stop, sizeof(StopLight));
	}

	for (int i = 0; i < num; i++) {
		obj[i]->Write(outDev);
	}

	outDev.write((char*)&dir, sizeof(dir));
	outDev.write((char*)&sleep, sizeof(sleep));
	outDev.write((char*)&timeCount, sizeof(timeCount));
	outDev.write((char*)&soundWaiting, sizeof(soundWaiting));
}

void Line::Read(istream& inDev)
{
	int num;
	Objects type;

	inDev.read((char*)&type, sizeof(type));
	inDev.read((char*)&width, sizeof(width));
	inDev.read((char*)&height, sizeof(height));
	inDev.read((char*)&pos, sizeof(pos));
	num = obj.size();

	inDev.read((char*)&num, sizeof(num));
	obj.resize(num);
	switch (type)
	{
	case BIRDS:
		for (int i = 0; i < num; i++) {
			obj[i] = new Birds();
		}

		stop = nullptr;
		break;
	case CARS:
		for (int i = 0; i < num; i++) {
			obj[i] = new Cars();
		}

		stop = new StopLight();
		inDev.read((char*)stop, sizeof(StopLight));
		break;

	case DINOSAURS:
		for (int i = 0; i < num; i++) {
			obj[i] = new Dinosaurs();
		}

		stop = nullptr;
		break;

	case TRUCKS:
		for (int i = 0; i < num; i++) {
			obj[i] = new Trucks();
		}

		stop = new StopLight();
		inDev.read((char*)stop, sizeof(StopLight));
		break;
	default:
		break;
	}

	for (int i = 0; i < num; i++) {
		obj[i]->Read(inDev);
	}

	inDev.read((char*)&dir, sizeof(dir));
	inDev.read((char*)&sleep, sizeof(sleep));
	inDev.read((char*)&timeCount, sizeof(timeCount));
	inDev.read((char*)&soundWaiting, sizeof(soundWaiting));
}

void Line::Located()
{
	if (!obj.empty()) {
		for (int i = 0; i < obj.size(); i++) {
			delete obj[i];
			obj[i] = nullptr;
		}
		obj.clear();
	}
	delete stop;
	stop = nullptr;
}
bool Line::IsInside(const People & people)
{
	COORD peoplePos = (const_cast<People&>(people)).GetPos();
	if (pos.Y <= peoplePos.Y && peoplePos.Y < pos.Y + height)
		return true;
	return false;
}
