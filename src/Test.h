/*
 * Test.h
 *
 *  Created on: 3 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <functional>

//boost
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

//lib
#include "../lib/easylogging++.h"
#include "fluidControl/executable/containers/actuators/communications/SerialSender.h"

//local
#include "graph/Graph.h"
#include "graph/Node.h"
#include "graph/Edge.h"
#include "graph/Flow.h"
#include "graph/FlowPtrComparator.h"

#include "testactuator/EvoprogContinuousPump.h"
#include "testactuator/EvoprogOdSensor.h"
#include "testactuator/EvoprogSixwayValve.h"
#include "testactuator/EvoprogLight.h"
#include "testactuator/EvoprogDiscretePump.h"
#include "testactuator/EvoprogMixer.h"
#include "testactuator/EvoprogTemperature.h"
#include "testactuator/EvoprogDummyInjector.h"

#include "util/Utils.h"
#include "util/AutoEnumerate.h"
#include "fluidControl/EvoCoder.h"
#include "fluidControl/machineGraph/MachineGraph.h"
#include "fluidControl/machineGraph/ContainerNode.h"
#include "fluidControl/machineGraph/ContainerNodeType.h"

#include "fluidControl/executable/containers/actuators/liquids/Control.h"
#include "fluidControl/executable/containers/actuators/liquids/Injector.h"
#include "fluidControl/executable/containers/actuators/liquids/Extractor.h"
#include "fluidControl/executable/containers/actuators/extras/Temperature.h"
#include "fluidControl/executable/containers/actuators/extras/ODSensor.h"
#include "fluidControl/executable/containers/actuators/extras/Light.h"
#include "fluidControl/executable/containers/actuators/extras/Mixer.h"
#include "fluidControl/executable/containers/InletContainer.h"
#include "fluidControl/executable/containers/BidirectionalSwitch.h"
#include "fluidControl/executable/containers/ConvergentSwitch.h"
#include "fluidControl/executable/containers/ConvergentSwitchInlet.h"
#include "fluidControl/executable/containers/DivergentSwitch.h"
#include "fluidControl/executable/containers/DivergentSwitchSink.h"
#include "fluidControl/executable/containers/ExecutableContainerNode.h"
#include "fluidControl/executable/containers/FlowContainer.h"
#include "fluidControl/executable/containers/SinkContainer.h"

#include "fluidControl/protocolGraph/ProtocolGraph.h"
#include "fluidControl/protocolGraph/ConditionEdge.h"
#include "operables/mathematics/ConstantNumber.h"
#include "operables/mathematics/ArithmeticOperation.h"
#include "operables/mathematics/UnaryOperation.h"
#include "operables/mathematics/MathematicOperable.h"
#include "operables/mathematics/VariableEntry.h"
#include "operables/VariableTable.h"
#include "operables/comparison/ComparisonOperable.h"
#include "operables/comparison/Tautology.h"
#include "operables/comparison/SimpleComparison.h"
#include "operables/comparison/BooleanComparison.h"

//operations
#include "fluidControl/protocolGraph/operations/AssignationOperation.h"
#include "fluidControl/protocolGraph/operations/container/ApplyLight.h"
#include "fluidControl/protocolGraph/operations/container/ApplyTemperature.h"
#include "fluidControl/protocolGraph/operations/container/ContainerOperation.h"
#include "fluidControl/protocolGraph/operations/container/GetVolume.h"
#include "fluidControl/protocolGraph/operations/container/LoadContainerOperation.h"
#include "fluidControl/protocolGraph/operations/container/MeasureOD.h"
#include "fluidControl/protocolGraph/operations/container/Mix.h"
#include "fluidControl/protocolGraph/operations/container/SetContinousFlow.h"
#include "fluidControl/protocolGraph/operations/container/TimeStep.h"
#include "fluidControl/protocolGraph/operations/container/Transfer.h"
#include "fluidControl/protocolGraph/operations/LoopNode.h"
#include "fluidControl/protocolGraph/operations/DivergeNode.h"
#include "graph/Flow.h"


INITIALIZE_EASYLOGGINGPP

using namespace std;

class Test {
public:
	static ProtocolGraph* MakeTurbidostat(
			boost::shared_ptr<VariableTable> table,
			boost::shared_ptr<Mapping> map);
	static ProtocolGraph* makeSimpleProtocol(
				boost::shared_ptr<VariableTable> table,
				boost::shared_ptr<Mapping> map);
	static ExecutableMachineGraph* makeSimpleMachine(CommandSender* communications);

	Test();
	virtual ~Test();

	void initLogger();

	void testGraph();
	void testContainerNode();
	void testUtils();
	void testVariableTable(boost::shared_ptr<VariableTable> t,  const std::string & name);
	void testMathematicVariable();
	void testComparisonVariable();
	void testUnaryOperation();
	void testSketcher();
	void testMapping();
	void testFlow();
	void testSerialPort_send();
	void testSerialPort_receive();
	void testExecutableMachineGraph();
	void testEvoprogComponents();

};

#endif /* SRC_TEST_H_ */
