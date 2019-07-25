#pragma once
#include "MyGame/MyApp.h"

namespace Eff1
{
	const char caTaskName[] = { "エフェクト１タスク" };
	const char caResName[] = { "エフェクト１リソース" };

	enum ChipType
	{
		TYPE_BEAM,
		TYPE_R_FRG,
		TYPE_Y_FRG,
		TYPE_B_FRG,
		TYPE_Y_STAR,
		TYPE_R_STAR,
		TYPE_B_STAR,
		TYPE_MAX
	};
	enum EffGroupType
	{
		EFFECT_TYPE_HOUKI,
		EFFECT_TYPE_HANABI
	};
	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/
		Image iEff1Img;

		RS() { Init(); }
		~RS() { Finalize(); }
	private:
		void Init();
		void Finalize();
	};
	typedef RS *RS_ptr;
	/*タスクオブジェクトクラス*/
	typedef class Obj : public TaskBase
	{
	public:
		/*必要なメンバはここに追加*/

		Obj() {}
		~Obj() {}
	private:
		Rec rEffBase;
		float fSpdX;
		float fSpdY;
		float fAddSpdX;
		float fAddSpdY;
		float fAngle;
		float fAddAngle;
		byte bLifeMax;
		byte bLife;
		ChipType tType;

		void Init();
		void Finalize();
	public:
		void Update();
		void Render();

		void SetParam(const Rec * const crpcEffBase, const Vector2 * const cvpcSpd, const byte cbLifeMax, const ChipType ctType, const float cfAngle = 0.f, const float cfAddAngle = 0.f, const Vector2 * const vAddSpd = &Vector2::zero);
	}*Obj_ptr;
	void CreateOugi(const int iNum, const ChipType cType, const Point * const pPos, const float fW, const float fH, const float fInitAngle, const float fMax, const float fMin, const byte bLife = 20, const float fSpd = 1.f, const Vector2 * const vAddSpd = &Vector2::zero);
	void CreateHanabi(const int iNum, const ChipType cType, const Point * const pPos, const float fW, const float fH, const float fInitAngle, const byte bLife = 20, const float fSpd = 1.f, const Vector2 * const vAddSpd = &Vector2::zero);
	void Create(const std::string &asEfFileName, const Point * const apPos, const float afAngle);

	class EffectCreater
	{
	private:
		static const std::map<const std::string, const Eff1::ChipType> m_type;
		std::string ef_type, ch_type;
		int num, life;
		float w, h, op[2], spd;
	public:
		using SP = std::shared_ptr<EffectCreater>;
		EffectCreater(const std::string &_filename)
			: ef_type("nothing")
			, ch_type("nothing")
		{
			std::ifstream _ifs(_filename);
			if (!_ifs) return;
			std::string _cmd;
			for (;;)
			{
				/*ファイルの終端*/
				if (_ifs.eof()) break;
				_ifs >> _cmd;
				/*コメント*/
				if (_cmd.at(0) == '\'')
				{
					_ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				/*終了*/
				if (_cmd == "end") break;
				/*エフェクトタイプ*/
				if (_cmd == "e_type")
				{
					_ifs >> ef_type;
					continue;
				}
				/*チップタイプ*/
				if (_cmd == "c_type")
				{
					_ifs >> ch_type;
					continue;
				}
				/*サイズ*/
				if (_cmd == "c_size")
				{
					_ifs >> w >> h;
					continue;
				}
				/*個数*/
				if (_cmd == "num")
				{
					_ifs >> num;
					continue;
				}
				/*寿命*/
				if (_cmd == "life")
				{
					_ifs >> life;
					continue;
				}
				/*速さ*/
				if (_cmd == "spd")
				{
					_ifs >> spd;
					continue;
				}
				/*オプション*/
				if (_cmd == "op")
				{
					int _idx = 0;
					_ifs >> _idx;
					if (_idx >= sizeof(op) / sizeof(op[0]))
					{
						MsgBox(_filename + " インデックスがオプションの最大数を超えています。");
						break;
					}
					_ifs >> op[_idx];
					continue;
				}
			}
			_ifs.close();
		}
		void run(const Point &_pos, const float _angle) const
		{
			if (ef_type == "nothing" || ch_type == "nothing") return;
			if (ef_type == "ougi")
			{
				CreateOugi(num, m_type.at(ch_type), &_pos, w, h, _angle, op[0], op[1], life, spd);
			}
			else if (ef_type == "hanabi")
			{
				CreateHanabi(num, m_type.at(ch_type), &_pos, w, h, _angle, life, spd, &Vector2(op[0], op[1]));
			}
		}
		void _set_chip_type(const std::string &_ch_type)
		{
			ch_type = _ch_type;
		}
	};
}