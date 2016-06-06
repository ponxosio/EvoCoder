/*
 * Test.h
 *
 *  Created on: 3 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <functional>
#include <iostream>
#include <sstream>
#include <memory>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>

#include <unordered_map>
#include <tuple>

//boost
#include <boost/function.hpp>
#include <boost/python.hpp>
#include <memory>

//lib
#include <easylogging++.h>


//local
#include "ExecutionServer.h"

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
#include "util/ContainersUtils.h"

#include "fluidControl/ExecutionEngine.h"
#include "fluidControl/mapping/MappingEngine.h"
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

#include "fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"
#include "fluidControl/executable/containers/actuators/communications/CommandSender.h"
#include "fluidControl/executable/containers/actuators/communications/FileSender.h"
#include "fluidControl/executable/containers/actuators/communications/SerialSender.h"

#include "fluidControl/executable/containers/InletContainer.h"
#include "fluidControl/executable/containers/BidirectionalSwitch.h"
#include "fluidControl/executable/containers/ConvergentSwitch.h"
#include "fluidControl/executable/containers/ConvergentSwitchInlet.h"
#include "fluidControl/executable/containers/DivergentSwitch.h"
#include "fluidControl/executable/containers/DivergentSwitchSink.h"
#include "fluidControl/executable/containers/ExecutableContainerNode.h"
#include "fluidControl/executable/containers/FlowContainer.h"
#include "fluidControl/executable/containers/SinkContainer.h"

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

//flow
#include "fluidControl\mapping\pathcalculator\PathManager.h"

//plugins
#include "plugin/PluginFileLoader.h"
#include "plugin/PythonEnvironment.h"
#include "plugin/actuators/ODSensorPlugin.h"
#include "plugin/actuators/MixerPlugin.h"
#include "plugin/actuators/TemperaturePlugin.h"
#include "plugin/actuators/LightPlugin.h"
#include "plugin/actuators/ControlPlugin.h"
#include "plugin/actuators/ExtractorPlugin.h"
#include "plugin/actuators/InjectorPlugin.h"

//operations
#include "graph/Flow.h"
#include "protocolGraph/ConditionEdge.h"
#include "protocolGraph/operations/AssignationOperation.h"
#include "protocolGraph/operations/container/ApplyLight.h"
#include "protocolGraph/operations/container/ApplyTemperature.h"
#include "protocolGraph/operations/container/ContainerOperation.h"
#include "protocolGraph/operations/container/GetVolume.h"
#include "protocolGraph/operations/container/LoadContainerOperation.h"
#include "protocolGraph/operations/container/MeasureOD.h"
#include "protocolGraph/operations/container/Mix.h"
#include "protocolGraph/operations/container/SetContinousFlow.h"
#include "protocolGraph/operations/container/TimeStep.h"
#include "protocolGraph/operations/container/Transfer.h"
#include "protocolGraph/operations/DivergeNode.h"
#include "protocolGraph/operations/LoopNode.h"
#include "protocolGraph/ProtocolGraph.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/tuple.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>


INITIALIZE_EASYLOGGINGPP

using namespace std;

class Test {
public:
	static ProtocolGraph* MakeTurbidostat(
			std::shared_ptr<VariableTable> table,
			std::shared_ptr<Mapping> map);
	static ProtocolGraph* makeTimeProtocol(
		std::shared_ptr<VariableTable> table,
		std::shared_ptr<Mapping> map);
	static ProtocolGraph* makeSimpleProtocol(
				std::shared_ptr<VariableTable> table,
				std::shared_ptr<Mapping> map);
	static ExecutableMachineGraph* makeSimpleMachine(int communications, std::unique_ptr<CommandSender> exec, std::unique_ptr<CommandSender> test);
	static ExecutableMachineGraph* makeSimpleMachinePlugin(int communications, std::unique_ptr<CommandSender> exec, std::unique_ptr<CommandSender> test);
	static ExecutableMachineGraph* makeMatrixMachine(int communications, std::unique_ptr<CommandSender> exec, std::unique_ptr<CommandSender> test, int size);
	static ExecutableMachineGraph* makeMappingMachine(int communications, std::unique_ptr<CommandSender> exec, std::unique_ptr<CommandSender> test);
	static MachineGraph* makeTurbidostatSketch();
	static MachineGraph* makeMatrixSketch(int size);

	Test();
	virtual ~Test();

	void initLogger();

	void testGraph();
	void testContainerNode();
	void testUtils();
	void testVariableTable(std::shared_ptr<VariableTable> t,  const std::string & name);
	void testMathematicVariable();
	void testComparisonVariable();
	void testUnaryOperation();
	void testSketcher();
	void testMapping();
	void testFlow();
	void testSerialPort_send();
	void testSerialPort_receive();
	void testExecutableMachineGraph();
	void testExecutableMachineGraphPerformance();
	void testEvoprogComponents();
	void testCalculateSubgraphs();
	void testContainerNodeType();
	void testCompatibleSubgraph();
	void testMappingEngine();
	void testMappingEnginePerformance();
	void testCommunicationsInterface();
	void testFileCommandSender();

	void testMappingTest();
	void testMappingExec();

	void testSerializeNode();
	void testSerializeMachine();

	void testTimeStep();
	void testTimeStepTest();

	void testSerializaVariableTable();
	void testDeserializaVariableTable(const std::string & json);

	void testSerialize_MathematicOperable();
	void testSerialize_ExecutableConatinerNode();

	void pythonTest();
	void testPythonEnvironment();

	void pluinLoaderTest();

	void testOdSensorPlugin();

	void testMappingPluginTest();
	void testMappingPluginExec();

	void testExecutionServer();

	class Chorra {
	public:
		Chorra() {
			this->i = -1;
		}
		Chorra(int i) {
			this->i = i;
		}
		inline int getI() {
			return i;
		}

		int i;
	};
};

BOOST_PYTHON_MODULE(ChorraMod)
{
	boost::python::class_<Test::Chorra>("Test::Chorra")
		.def("getI", &Test::Chorra::getI)
		;
}

#endif /* SRC_TEST_H_ */
