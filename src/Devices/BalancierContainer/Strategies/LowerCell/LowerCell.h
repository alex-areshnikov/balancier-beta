#include "../Base/Base.h"
#include <vector>

namespace Balancier {
	namespace Strategies {
		class LowerCell: public Balancier::Strategies::Base {
			private:
				std::vector<float> voltages;
			public:
				LowerCell(std::vector<float>);
				float balanceVoltage();
		};
	};
};