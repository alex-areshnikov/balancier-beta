// #include <ArduinoSTL.h>
// #include <vector>
// #include "../CellController/CellController.h"
// #include "Services/Wakeupper/Wakeupper.h"
// #include "../Strategies/Base/Base.h"
// #include "../Strategies/FixedLimit/FixedLimit.h"
// #include "../Strategies/LowerCell/LowerCell.h"

// namespace Balancier {
// 	class Manager {
// 		private:
// 			static const uint8_t NO_CHANGE = 0xE0;

// 			static const uint8_t FIXED_LIMIT_STRATEGY = 0x10;
// 			static const uint8_t LOWER_CELL_STRATEGY = 0x11;

// 			static const uint8_t S1 = 0x7;
// 			static const uint8_t S2 = 0x2;
// 			static const uint8_t S3 = 0x3;
// 			static const uint8_t S4 = 0x4;
// 			static const uint8_t S5 = 0x5;
// 			static const uint8_t S6 = 0x6;
			
// 			static const int WAKEUP_INTERVAL_MS = 50;

// 			Wakeupper *wakeupper;			
// 			std::vector<CellController *> cellControllers;
// 			Balancier::Strategies::Base *balancingStrategy;
// 		public:
// 			Manager();

// 			void process(std::vector<float>, uint8_t);
// 			void setStrategy(std::vector<float>, uint8_t);
// 			void setBalanceVoltage();
// 	};
// };