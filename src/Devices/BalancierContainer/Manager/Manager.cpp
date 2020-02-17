// #include "Manager.h"

// Balancier::Manager::Manager() {
// 	wakeupper = new Wakeupper(WAKEUP_INTERVAL_MS);

// 	cellControllers.push_back(new CellController(S1));
// 	cellControllers.push_back(new CellController(S2));
// 	cellControllers.push_back(new CellController(S3));
// 	cellControllers.push_back(new CellController(S4));
// 	cellControllers.push_back(new CellController(S5));
// 	cellControllers.push_back(new CellController(S6));	
// }

// void Balancier::Manager::process(std::vector<float> voltages, uint8_t strategy = NO_CHANGE) {
// 	if (!wakeupper->isWakeupTime()) return;	

// 	for (auto element = cellControllers.begin(); element != cellControllers.end(); ++element) {
//     auto index = std::distance(cellControllers.begin(), element); 

//     (*element)->setVoltage(voltages.at(index));
// 		(*element)->process();
// 	}

// 	setStrategy(voltages, strategy);
// }

// void Balancier::Manager::setStrategy(std::vector<float> voltages, uint8_t strategy) {
// 	if(strategy == NO_CHANGE) return;

// 	switch(strategy) {
// 		case FIXED_LIMIT_STRATEGY:
// 			balancingStrategy = static_cast<Balancier::Strategies::FixedLimit *>(balancingStrategy);
// 			balancingStrategy = new Balancier::Strategies::FixedLimit(2.55);
// 			break;	
// 		case LOWER_CELL_STRATEGY:	
// 			balancingStrategy = static_cast<Balancier::Strategies::LowerCell *>(balancingStrategy);
// 			balancingStrategy = new Balancier::Strategies::LowerCell(voltages);
// 		default:
// 			// throw "Unknown Balancing Strategy";
// 			break;
// 	}

// 	setBalanceVoltage();
// }

// void Balancier::Manager::setBalanceVoltage() {
// 	for (CellController *cellController : cellControllers) {
// 		cellController->balanceTo(balancingStrategy->balanceVoltage());
// 	}
// }