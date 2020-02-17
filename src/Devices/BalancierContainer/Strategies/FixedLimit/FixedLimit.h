#include "../Base/Base.h"

namespace Balancier {
	namespace Strategies {
		class FixedLimit: public Balancier::Strategies::Base {
			private:
				float limit;
			public:
				FixedLimit(float);
				float balanceVoltage();
		};
	};
};