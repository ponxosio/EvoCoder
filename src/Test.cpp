/*
 * Test.cpp
 *
 *  Created on: 3 de mar. de 2016
 *      Author: angel
 */

#include "Test.h"

using namespace std;

//#define _QUESO
Test::Test() {
	// TODO Auto-generated constructor stub

}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

int main(int argv, char* argc[]) {
	Test t;
	t.initLogger();

	LOG(INFO) << "started!...";

	//t.testGraph();
	/* t.testContainerNode();
	 t.testVariableTable();
	 t.testComparisonVariable();
	 t.testComparisonVariable();
	 */
	 //std::shared_ptr<VariableTable> table(new VariableTable());
	 //t.testVariableTable(table, "wikiwiki");
 //	t.testMathematicVariable();
	 //t.testUnaryOperation();
	 //t.testSketcher();
	 //t.testMapping();
	 //t.testFlow();
	 //t.testExecutableMachineGraph();
	 //t.testExecutableMachineGraphPerformance();
	 //t.testCalculateSubgraphs();
	 //t.testContainerNodeType();
	 //t.testCompatibleSubgraph();

	 //t.testSerialPort_send();

	 //t.testSerialPort_receive();

	 //t.testMappingEngine();
	 t.testMappingEnginePerformance();

	 //t.testCommunicationsInterface();
	 //t.testFileCommandSender();

	//t.testMappingTest();
	//t.testMappingExec();

	//t.testSerializaVariableTable();
	/*t.testSerialize_MathematicOperable();
	t.testSerialize_ExecutableConatinerNode();
	t.testSerializeNode();*/
	//t.testSerializeMachine();

	//t.testTimeStep();
	//t.testTimeStepTest();

	//t.pythonTest();
	//t.testPythonEnvironment();
	//t.pluinLoaderTest();

	//t.testOdSensorPlugin();

	//t.testMappingPluginTest();
	//t.testMappingPluginExec();

	//t.testExecutionServer();

	//t.testFlowCalculatorIntensive();

	//t.testPathManager();

	//t.testMappingIntensive();

	LOG(INFO) << "finished!";
}

void Test::testGraph() {
	{
		std::shared_ptr<Graph<Node, Edge>> g = std::make_shared<Graph<Node, Edge>>();

		if (g->addNode(std::make_shared<Node>(0)) && g->addNode(std::make_shared<Node>(1))
			&& g->addNode(std::make_shared<Node>(2)) && g->addEdge(std::make_shared<Edge>(0, 1))
			&& g->addEdge(std::make_shared<Edge>(1, 2)) && g->addNode(std::make_shared<Node>(3)) && g->addEdge(std::make_shared<Edge>(3, 1)) && g->saveGraph("preserialize.graph")) {
		}
		else {
			LOG(ERROR) << "error creating and saving graph";
		}

		const Graph<Node, Edge>::EdgeVectorPtr arriving = g->getArrivingEdges(1);
		LOG(INFO) << "arriving edges to 1: 0->1, 3->1";
		for (auto it = arriving->begin(); it != arriving->end(); ++it) {
			LOG(INFO) << (*it)->toText();
		}

		const Graph<Node, Edge>::EdgeVectorPtr leaving = g->getLeavingEdges(1);
		LOG(INFO) << "leaving edges to 1: 1->2";
		for (auto it = leaving->begin(); it != leaving->end(); ++it) {
			LOG(INFO) << (*it)->toText();
		}


		ofstream o("test.json");
		LOG(INFO) << "serializating...";
		try {
			cereal::JSONOutputArchive ar(o);
			ar(g);
		}
		catch (cereal::Exception & e) {
			LOG(FATAL) << "exception while serializating, " << e.what();
		}
	}
	{
		std::shared_ptr<Graph<Node, Edge>> g;
		ifstream i("test.json");
		try {
			cereal::JSONInputArchive arIn(i);
			LOG(INFO) << "created archive...";
			arIn(g);
			g->saveGraph("postserilize.graph");
		}
		catch (cereal::Exception& e) {
			LOG(FATAL) << "exception while de-serializating, " << e.what();
		}
	}
}

void Test::testContainerNode() {
	Graph<ContainerNode, Edge>* g = new Graph<ContainerNode, Edge>();

	if (g->addNode(
		std::make_shared<ContainerNode>(0,
			std::shared_ptr<ContainerNodeType>(
				new ContainerNodeType(MovementType::continuous,
					ContainerType::inlet)), 10.0f))
		&& g->addNode(
			std::make_shared<ContainerNode>(1,
				std::shared_ptr<ContainerNodeType>(
					new ContainerNodeType(
						MovementType::continuous,
						ContainerType::flow)), 10.0f))
		&& g->addNode(
			std::make_shared<ContainerNode>(2,
				std::shared_ptr<ContainerNodeType>(
					new ContainerNodeType(
						MovementType::irrelevant,
						ContainerType::sink)), 10.0f))
		&& g->addEdge(std::make_shared<Edge>(0, 1)) && g->addEdge(std::make_shared<Edge>(1, 2))
		&& g->saveGraph("test_container.graph")) {
	}
	else {
		LOG(ERROR) << "error creating and saving graph";
	}
	delete g;
}

void Test::initLogger() {
	// Load configuration from file
	el::Configurations conf(".\\configuration\\log.ini");
	// Actually reconfigure all loggers instead
	el::Loggers::reconfigureAllLoggers(conf);
}

void Test::testUtils() {
	string line = "Hola	que tal";
	vector<string> vec;

	Utils::tokenize(line, vec);
	for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {
		LOG(DEBUG) << *it << endl;
	}
}

void Test::testVariableTable(std::shared_ptr<VariableTable> t,
	const std::string & name) {
	t->setValue("tiempo", 0.0);
	LOG(INFO) << "valor para tiempo(0.0) = " << patch::to_string(t->getVaue("tiempo"));
	t->setValue("tiempo", 1.0);
	LOG(INFO) << "valor para tiempo(1.0) = " << patch::to_string(t->getVaue("tiempo"));

	LOG(INFO) << "physical para tiempo(0) = " << patch::to_string(t->getPhysical("tiempo"));
	t->setPhysical("tiempo", true);
	LOG(INFO) << "physical para tiempo(1) = " << patch::to_string(t->getPhysical("tiempo"));

	try {
		t->getVaue(name);
	}
	catch (invalid_argument & e) {
		LOG(INFO) << "excepcion invalid_argument = " << e.what();
	}
}

void Test::testMathematicVariable() {
	LOG(INFO) << "TEST MATHEMATIC VARIABLE...";
	std::shared_ptr<VariableTable> t(new VariableTable());

	std::shared_ptr<MathematicOperable> ve(new VariableEntry("test"));
	std::shared_ptr<MathematicOperable> ve2(new VariableEntry("test2"));

	t->setValue("test", 3.0);
	t->setValue("test2", 2.0);

	std::shared_ptr<MathematicOperable> cn(new ConstantNumber(7.0));
	std::shared_ptr<MathematicOperable> ao(new ArithmeticOperation(ve, arithmetic::minus, cn));
	std::shared_ptr<MathematicOperable> ao2(new ArithmeticOperation(ve2, arithmetic::multiply, ao));
	std::shared_ptr<MathematicOperable> ao22(new ArithmeticOperation(ve2, arithmetic::multiply, ao));

	LOG(INFO) << "test(3) - 7 = -4 : " << patch::to_string(ao.get()->getValue());
	LOG(INFO) << "test2(2) * (test(3) - 7) = -8 : " << patch::to_string(ao2.get()->getValue());

	LOG(INFO) << "ao2 == ao22 ? TRUE : " << ao22.get()->equal(ao2.get());
	LOG(INFO) << "ao2 == ve2 ? FALSE : " << ao22.get()->equal(ve2.get());

	t->setValue("test", 5.0);
	LOG(INFO) << "test(5) - 7 = -2 : " << patch::to_string(ao.get()->getValue());

	std::shared_ptr<MathematicOperable> ao222 = ao22;
	LOG(INFO) << "ao22 == ao22 : " << ao22.get()->equal(ao222.get());

}

void Test::testComparisonVariable() {
	LOG(INFO) << "TEST COMPARISON VARIABLE...";
	std::shared_ptr<VariableTable> t(new VariableTable());
	t->setValue("test", 3);
	t->setValue("test2", 2);

	std::shared_ptr<MathematicOperable> ve(new VariableEntry("test"));
	std::shared_ptr<MathematicOperable> ve2(new VariableEntry("test2"));
	std::shared_ptr<MathematicOperable> cn7(new ConstantNumber(7.0));
	std::shared_ptr<MathematicOperable> cn1(new ConstantNumber(1.0));
	std::shared_ptr<MathematicOperable> ao(new ArithmeticOperation(ve, arithmetic::minus, cn7));

	//test

	std::shared_ptr<ComparisonOperable> sc1(new SimpleComparison(false, ve, comparison::greater_equal, cn7));
	std::shared_ptr<ComparisonOperable> sc2(new SimpleComparison(false, ve, comparison::less, ve2));

	std::shared_ptr<ComparisonOperable> sc3(new SimpleComparison(true, ve, comparison::greater_equal, cn7));
	std::shared_ptr<ComparisonOperable> sc4(new SimpleComparison(false, ve, comparison::greater_equal, cn1));
	std::shared_ptr<ComparisonOperable> bc(new BooleanComparison(false, sc4, logical::conjunction, sc3));

	LOG(INFO) << "test(3) >= 7 : " << sc1.get()->conditionMet();
	t->setValue("test", 7.0);
	LOG(INFO) << "test(7) >= 7 : " << sc1.get()->conditionMet();

	LOG(INFO) << "test(7) < test2(2) : " << sc2.get()->conditionMet();

	t->setValue("test", 3.0);
	LOG(INFO) << "!(test(3) >= 7.0) : " << sc3.get()->conditionMet();
	LOG(INFO) << "test(3) >= 1 : " << sc4.get()->conditionMet();
	LOG(INFO) << "(test(3) >= 1) && !(test(3) >= 7) : " << bc.get()->conditionMet();

	LOG(INFO) << "sc1 == sc3 (FALSE) : " << sc1.get()->equal(sc3.get());
	LOG(INFO) << "bc == bc (TRUE) : " << bc.get()->equal(bc.get());
	LOG(INFO) << "sc1 == bc (FALSE) : " << sc1.get()->equal(bc.get());
}

ProtocolGraph* Test::MakeTurbidostat(std::shared_ptr<VariableTable> table,
	std::shared_ptr<Mapping> map) {

	AutoEnumerate serial;
	ProtocolGraph* protocol = new ProtocolGraph("turbidostat");

	std::shared_ptr<VariableEntry> epsilon(
		new VariableEntry("epsilon"));
	std::shared_ptr<VariableEntry> threshold(
		new VariableEntry("threshold"));
	std::shared_ptr<VariableEntry> rate(new VariableEntry("rate"));

	std::shared_ptr<MathematicOperable> mepsilon(
		new VariableEntry("epsilon"));
	std::shared_ptr<MathematicOperable> mthreshold(
		new VariableEntry("threshold"));
	std::shared_ptr<MathematicOperable> mrate(
		new VariableEntry("rate"));

	std::shared_ptr<MathematicOperable> num0_1(new ConstantNumber(0.1));
	std::shared_ptr<MathematicOperable> num600(new ConstantNumber(600));
	std::shared_ptr<MathematicOperable> num2(new ConstantNumber(2));

	ProtocolGraph::ProtocolNodePtr op1 = std::make_shared<AssignationOperation>(serial.getNextValue(),
		epsilon, num0_1); //epsilon = 1
	protocol->setStartNode(op1->getContainerId());

	ProtocolGraph::ProtocolNodePtr op2 = std::make_shared<AssignationOperation>(serial.getNextValue(),
		threshold, num600); //threshold = 600
	ProtocolGraph::ProtocolNodePtr op3 = std::make_shared<AssignationOperation>(serial.getNextValue(), rate,
		num2); //rate = 2

	protocol->addOperation(op1);
	protocol->addOperation(op2);
	protocol->addOperation(op3);

	std::shared_ptr<ComparisonOperable> tautology(new Tautology());
	protocol->connectOperation(op1, op2, tautology);
	protocol->connectOperation(op2, op3, tautology);

	std::shared_ptr<MathematicOperable> num1000(new ConstantNumber(1000));
	ProtocolGraph::ProtocolNodePtr op4 = std::make_shared<LoadContainerOperation>(serial.getNextValue(), 1, num1000); //loadContainer(1, 1000ml)
	ProtocolGraph::ProtocolNodePtr op5 = std::make_shared<LoadContainerOperation>(serial.getNextValue(), 2, num1000); //loadContainer(2, 1000ml)
	ProtocolGraph::ProtocolNodePtr op6 = std::make_shared<LoadContainerOperation>(serial.getNextValue(), 3, num1000); //loadContainer(3, 1000ml)

	protocol->addOperation(op4);
	protocol->addOperation(op5);
	protocol->addOperation(op6);

	protocol->connectOperation(op3, op4, tautology);
	protocol->connectOperation(op4, op5, tautology);
	protocol->connectOperation(op5, op6, tautology);

	std::shared_ptr<MathematicOperable> num20(new ConstantNumber(20000));
	std::shared_ptr<VariableEntry> time(
		new VariableEntry(TIME_VARIABLE));
	std::shared_ptr<MathematicOperable> mtime(
		new VariableEntry(TIME_VARIABLE));

	std::shared_ptr<ComparisonOperable> comp1(
		new SimpleComparison(false, mtime, comparison::less, num20));

	ProtocolGraph::ProtocolNodePtr loop1 = std::make_shared<LoopNode>(serial.getNextValue(), comp1); //while (t < 20)

	protocol->addOperation(loop1);
	protocol->connectOperation(op6, loop1, comp1);

	std::shared_ptr<VariableEntry> od(new VariableEntry("od"));
	std::shared_ptr<MathematicOperable> mod(new VariableEntry("od"));
	ProtocolGraph::ProtocolNodePtr op7 = std::make_shared<MeasureOD>(serial.getNextValue(), 2, od); //od = measureOd(2)

	protocol->addOperation(op7);
	protocol->connectOperation(loop1, op7, comp1);

	std::shared_ptr<MathematicOperable> num1(new ConstantNumber(1.0));
	std::shared_ptr<VariableEntry> normOD(new VariableEntry("normOD"));
	std::shared_ptr<MathematicOperable> mnormOD(
		new VariableEntry("normOD"));

	std::shared_ptr<MathematicOperable> operation1_1( //(od - threshold)
		new ArithmeticOperation(mod, arithmetic::minus, mthreshold));
	std::shared_ptr<MathematicOperable> operation1_2( //(od - threshold) /threshold
		new ArithmeticOperation(operation1_1, arithmetic::divide,
			mthreshold));
	std::shared_ptr<MathematicOperable> operation1( //1 + (od - threshold) /threshold
		new ArithmeticOperation(num1, arithmetic::plus, operation1_2));

	ProtocolGraph::ProtocolNodePtr op8 = std::make_shared<AssignationOperation>(serial.getNextValue(), normOD,
		operation1); // normOD = 1 + (od - threshold) /threshold

	protocol->addOperation(op8);
	protocol->connectOperation(op7, op8, tautology);

	std::shared_ptr<ComparisonOperable> comp2in(
		new SimpleComparison(false, normOD, comparison::greater, num1));
	std::shared_ptr<ComparisonOperable> comp2out(
		new SimpleComparison(true, normOD, comparison::greater, num1));
	ProtocolGraph::ProtocolNodePtr if1 = std::make_shared<DivergeNode>(serial.getNextValue(), comp2in); //if (normOD > 1)

	protocol->addOperation(if1);
	protocol->connectOperation(op8, if1, tautology);

	std::shared_ptr<ComparisonOperable> comp3in(
		new SimpleComparison(false, normOD, comparison::less, num1));
	std::shared_ptr<ComparisonOperable> comp3out(
		new SimpleComparison(true, normOD, comparison::less, num1));
	ProtocolGraph::ProtocolNodePtr if2 = std::make_shared<DivergeNode>(serial.getNextValue(), comp3in); //if (normOD < 1)

	std::shared_ptr<MathematicOperable> operation2_1( //(normOD - 1)
		new ArithmeticOperation(mnormOD, arithmetic::minus, num1));
	std::shared_ptr<MathematicOperable> operation2( // 1 + (normOD - 1)
		new ArithmeticOperation(num1, arithmetic::plus, operation2_1));

	std::shared_ptr<VariableEntry> prop(new VariableEntry("prop"));
	std::shared_ptr<MathematicOperable> mprop(
		new VariableEntry("prop"));
	ProtocolGraph::ProtocolNodePtr op9 = std::make_shared<AssignationOperation>(serial.getNextValue(), prop,
		operation2); // prop = 1 + (normOD - 1)

	protocol->addOperation(if2);
	protocol->addOperation(op9);

	protocol->connectOperation(if1, op9, comp2in);
	protocol->connectOperation(if1, if2, comp2out);

	std::shared_ptr<MathematicOperable> operation3_1( //(normOD - 1)
		new ArithmeticOperation(mnormOD, arithmetic::minus, num1));
	std::shared_ptr<MathematicOperable> operation3( // 1 - (normOD - 1)
		new ArithmeticOperation(num1, arithmetic::minus, operation2_1));

	ProtocolGraph::ProtocolNodePtr op10 = std::make_shared<AssignationOperation>(serial.getNextValue(), prop,
		operation3); // prop = 1 - (normOD - 1)

	ProtocolGraph::ProtocolNodePtr op11 = std::make_shared<AssignationOperation>(serial.getNextValue(), prop,
		num1); //prop = 1

	protocol->addOperation(op10);
	protocol->addOperation(op11);

	protocol->connectOperation(if2, op10, comp3in);
	protocol->connectOperation(if2, op11, comp3out);

	std::shared_ptr<MathematicOperable> operation4_1(
		new ArithmeticOperation(mprop, arithmetic::minus, num1)); // prop -1
	std::shared_ptr<MathematicOperable> operation4(
		new UnaryOperation(operation4_1, unaryOperations::absoluteValue)); // fabs(prop -1)

	std::shared_ptr<ComparisonOperable> comp4in(
		new SimpleComparison(false, operation4, comparison::greater,
			epsilon)); // fabs(prop -1) -1 > epsilon
	std::shared_ptr<ComparisonOperable> comp4out(
		new SimpleComparison(true, operation4, comparison::greater,
			epsilon)); // !(fabs(prop -1) -1 > epsilon)

	ProtocolGraph::ProtocolNodePtr if3 = std::make_shared<DivergeNode>(serial.getNextValue(), comp4in); //if (fabs(prop -1) -1 > epsilon)

	protocol->addOperation(if3);

	protocol->connectOperation(op9, if3, tautology);
	protocol->connectOperation(op10, if3, tautology);
	protocol->connectOperation(op11, if3, tautology);

	std::shared_ptr<MathematicOperable> operation5(
		new ArithmeticOperation(prop, arithmetic::multiply, rate)); // prop * rate
	ProtocolGraph::ProtocolNodePtr op12 = std::make_shared<AssignationOperation>(serial.getNextValue(), rate,
		operation5); // rate = prop * rate

	protocol->addOperation(op12);
	protocol->connectOperation(if3, op12, comp4in);

	ProtocolGraph::ProtocolNodePtr op13 = std::make_shared<SetContinousFlow>(serial.getNextValue(), 1, 2,
		rate); // setcontinousFlow(1,2,rate)

	protocol->addOperation(op13);
	protocol->connectOperation(op12, op13, tautology);

	ProtocolGraph::ProtocolNodePtr op14 = std::make_shared<SetContinousFlow>(serial.getNextValue(), 2, 3,
		rate); // setcontinousFlow(2,3,rate)

	protocol->addOperation(op14);
	protocol->connectOperation(op13, op14, tautology);

	ProtocolGraph::ProtocolNodePtr timeStep = std::make_shared<TimeStep>(serial.getNextValue(), time);

	protocol->addOperation(timeStep);

	protocol->connectOperation(op14, timeStep, tautology);
	protocol->connectOperation(if3, timeStep, comp4out);
	protocol->connectOperation(timeStep, loop1, tautology);

	return protocol;
}

void Test::testUnaryOperation() {
	std::shared_ptr<ConstantNumber> cn(new ConstantNumber(3.3));
	UnaryOperation op(cn, unaryOperations::absoluteValue);
	LOG(INFO) << "abs(3.3):" << patch::to_string(op.getValue());
}

void Test::testSketcher() {
	std::shared_ptr<VariableTable> t(new VariableTable());
	std::shared_ptr<ExecutableMachineGraph> machine(new ExecutableMachineGraph("testMachine", std::unique_ptr<CommandSender>(new SerialSender()), std::unique_ptr<CommandSender>(new FileSender())));
	std::vector<int> v;
	std::shared_ptr<Mapping> map(new Mapping(machine, "testMamchine", v));

	std::shared_ptr<ProtocolGraph> protocol(makeSimpleProtocol(t, map));

	LOG(INFO) << "printing protocol...";
	protocol->printProtocol("protocol.graph");

	ExecutionEngine* evo = new ExecutionEngine(protocol, t, map);

	LOG(INFO) << "Sketching... " << evo->sketcher();
	LOG(INFO) << "printing sketch...";
	map->printSketch("turbidostatMachine.graph");

	delete evo;
}

void Test::testMapping() {
	std::unique_ptr<CommandSender> exec(new SerialSender());
	std::unique_ptr<CommandSender> test(new FileSender());

	std::shared_ptr<VariableTable> t(new VariableTable());
	std::shared_ptr<ProtocolGraph> protocol(new ProtocolGraph("testProtocol"));
	std::shared_ptr<ExecutableMachineGraph> machine(new ExecutableMachineGraph("testMachine", std::move(exec), std::move(test)));
	std::vector<int> v;
	std::shared_ptr<Mapping> map = std::shared_ptr<Mapping>(new Mapping(machine, "test", v));

	ExecutionEngine* evo = new ExecutionEngine(protocol, t, map);

	map->setSketching();

	//test: actuador antes de declarar nodo
	map->setContinuosFlow(1, 2, 0.0);
	map->setContinuosFlow(2, 3, 0.0);
	map->measureOD(2);
	map->stir(2, 0.0);

	LOG(INFO) << "Sketching... " << evo->sketcher();
	map->printSketch("mappingTest.graph");

	delete evo;
}

void Test::testFlow() {
	std::priority_queue<Flow<Edge>*, vector<Flow<Edge>*>,
		FlowPtrComparator<Edge>> heap;

	Flow<Edge>* f1 = new Flow<Edge>(1, 3);
	Flow<Edge>::FlowEdgePtr edge13 = std::make_shared<Edge>(1, 3);
	f1->append(edge13);

	heap.push(f1);

	Flow<Edge>* f2 = new Flow<Edge>(1, 3);
	Flow<Edge>::FlowEdgePtr edge12 = std::make_shared<Edge>(1, 2);
	f2->append(edge12);
	f2->append(edge13);

	heap.push(f2);

	while (!heap.empty()) {
		Flow<Edge>* actual = heap.top();
		heap.pop();
		LOG(INFO) << actual->toText();
	}

}
void Test::testSerialPort_send() {
	try {
		SerialSender* s = new SerialSender("\\\\.\\COM3");

		for (int i = 0; i < 10; i++) {
			LOG(INFO) << "sending " << i << "...";
			LOG(INFO) << "correct: " << s->sendString(patch::to_string(i));
			Sleep(2000);
		}

	}
	catch (std::ios_base::failure& e) {
		LOG(INFO) << "error: " << e.what();
	}
}

ProtocolGraph* Test::makeSimpleProtocol(std::shared_ptr<VariableTable> table,
	std::shared_ptr<Mapping> map) {

	AutoEnumerate serial;
	ProtocolGraph* protocol = new ProtocolGraph("simpleProtocol");

	std::shared_ptr<ComparisonOperable> tautology(new Tautology());

	std::shared_ptr<VariableEntry> epsilon(
		new VariableEntry("epsilon"));
	std::shared_ptr<MathematicOperable> mepsilon(
		new VariableEntry("epsilon"));
	std::shared_ptr<MathematicOperable> num0_5(new ConstantNumber(0.5));
	std::shared_ptr<MathematicOperable> num10(new ConstantNumber(10));

	ProtocolGraph::ProtocolNodePtr op1 = std::make_shared<AssignationOperation>(serial.getNextValue(),
		epsilon, num0_5); //epsilon = 0.5

	std::shared_ptr<MathematicOperable> num1000(new ConstantNumber(1000));
	ProtocolGraph::ProtocolNodePtr op4 = std::make_shared<LoadContainerOperation>(serial.getNextValue(), 1, num1000); //loadContainer(1, 1000ml)
	ProtocolGraph::ProtocolNodePtr op5 = std::make_shared<LoadContainerOperation>(serial.getNextValue(), 2, num1000); //loadContainer(2, 1000ml)
	ProtocolGraph::ProtocolNodePtr op6 = std::make_shared<LoadContainerOperation>(serial.getNextValue(), 3, num1000); //loadContainer(3, 1000ml)

	protocol->addOperation(op1);
	protocol->addOperation(op4);
	protocol->addOperation(op5);
	protocol->addOperation(op6);

	protocol->connectOperation(op1, op4, tautology);
	protocol->connectOperation(op4, op5, tautology);
	protocol->connectOperation(op5, op6, tautology);

	std::shared_ptr<ComparisonOperable> contradiction(new Tautology());
	ProtocolGraph::ProtocolNodePtr loop1 = std::make_shared<LoopNode>(serial.getNextValue(), tautology); //while (true)

	protocol->addOperation(loop1);
	protocol->connectOperation(op6, loop1, tautology);

	std::shared_ptr<VariableEntry> od(new VariableEntry("od"));
	std::shared_ptr<MathematicOperable> mod(new VariableEntry("od"));
	ProtocolGraph::ProtocolNodePtr op7 = std::make_shared<MeasureOD>(serial.getNextValue(), 3, od); //od = measureOd(2)

	protocol->addOperation(op7);
	protocol->connectOperation(loop1, op7, tautology);

	std::shared_ptr<ComparisonOperable> comp2in(
		new SimpleComparison(false, mod, comparison::greater, mepsilon));
	std::shared_ptr<ComparisonOperable> comp2out(
		new SimpleComparison(true, mod, comparison::greater, mepsilon));
	ProtocolGraph::ProtocolNodePtr if1 = std::make_shared<DivergeNode>(serial.getNextValue(), comp2in); //if (od > 0.5)

	protocol->addOperation(if1);
	protocol->connectOperation(op7, if1, tautology);

	ProtocolGraph::ProtocolNodePtr op8 = std::make_shared<Transfer>(serial.getNextValue(), 1, 3, num10);
	ProtocolGraph::ProtocolNodePtr op9 = std::make_shared<Transfer>(serial.getNextValue(), 3, 4, num10);

	protocol->addOperation(op8);
	protocol->connectOperation(if1, op8, comp2in);
	protocol->addOperation(op9);
	protocol->connectOperation(op8, op9, tautology);
	protocol->connectOperation(op9, loop1, tautology);

	ProtocolGraph::ProtocolNodePtr op10 = std::make_shared<Transfer>(serial.getNextValue(), 2, 3, num10);
	ProtocolGraph::ProtocolNodePtr op11 = std::make_shared<Transfer>(serial.getNextValue(), 3, 4, num10);

	protocol->addOperation(op10);
	protocol->connectOperation(if1, op10, comp2out);
	protocol->addOperation(op11);
	protocol->connectOperation(op10, op11, tautology);
	protocol->connectOperation(op11, loop1, tautology);

	return protocol;
}

void Test::testSerialPort_receive() {
	try {
		CommandSender* s = new SerialSender("\\\\.\\COM3");

		LOG(INFO) << "recibiendo datos...";
		for (int i = 0; i < 10; i++) {
			LOG(INFO) << i << ":" << s->receiveString();
			Sleep(1500);
		}

	}
	catch (std::ios_base::failure& e) {
		LOG(INFO) << "error: " << e.what();
	}
}

void Test::testExecutableMachineGraph() {
	std::unique_ptr<CommandSender> comEx(new SerialSender("\\\\.\\COM3"));
	std::unique_ptr<CommandSender> comTest(new FileSender("test.log", "inputFileData.txt"));
	int communications = CommunicationsInterface::GetInstance()->addCommandSender(comEx->clone());

	LOG(INFO) << "creating machine...";
	std::shared_ptr<ExecutableMachineGraph> machine = std::shared_ptr<ExecutableMachineGraph>(makeMappingMachine(communications, std::move(comEx), std::move(comTest)));

	//ContainerNodeType cinlet(MovementType::continuous, ContainerType::inlet);
	ContainerNodeType cinlet(MovementType::continuous, ContainerType::flow);
	ContainerNodeType sink(MovementType::irrelevant, ContainerType::sink);

	LOG(INFO) << "printing graph...";
	machine->saveGraph("exMachine.graph");

	//machine->addUsedEdge(6, 2);
	//machine->addUsedNode(5);

	PathManager manager(machine);

	for (int i = 1; i < 8; i++) {
		LOG(INFO) << "gettings all paths from " << i;

		std::shared_ptr<PathSearcherIterator> it = manager.getPathSearcher(i,false);

		try {
			while (it->hasNext() != -1) {
				LOG(INFO) << it->next()->toText();
			}
		}
		catch (exception e) {
			LOG(ERROR) << e.what();
		}
	}

	for (int i = 1; i < 8; i++) {
		LOG(INFO) << "gettings all reverse paths from " << i;

		std::shared_ptr<PathSearcherIterator> it = manager.getPathSearcher(i, true);

		try {
			while (it->hasNext() != -1) {
				LOG(INFO) << it->next()->toText();
			}
		}
		catch (exception e) {
			LOG(ERROR) << e.what();
		}
	}

}

ExecutableMachineGraph* Test::makeRandomMachine(std::unique_ptr<CommandSender> exec, std::unique_ptr<CommandSender> test, int size) {
	ExecutableMachineGraph* machine = new ExecutableMachineGraph(
		"simpleMachine", std::move(exec), std::move(test));

	long seed = time(NULL);
	LOG(INFO) << "seed: " << seed;
	srand(seed);

	std::shared_ptr<Control> control(new EvoprogSixwayValve(0, 7));
	std::shared_ptr<Extractor> cExtractor13(
		new EvoprogContinuousPump(0, 13));
	std::shared_ptr<Extractor> cExtractor14(
		new EvoprogContinuousPump(0, 14));
	std::shared_ptr<Extractor> dExtractor(
		new EvoprogDiscretePump(0, 15));
	std::shared_ptr<Injector> dummyInjector(
		new EvoprogDummyInjector(0));

	for (int i = 0; i < size; i++) {
		ExecutableMachineGraph::ExecutableContainerNodePtr container = std::make_shared<BidirectionalSwitch>(i, 100.0, cExtractor14, dummyInjector, control, control);
		machine->addContainer(container);
	}

	for (int i = 0; i < size; i++) {
		int connections = rand() % 5;
		for (int j = 0; j < connections; j++) {
			int pair = rand() % (size-1);
			if (pair != i) {
				machine->connectExecutableContainer(i, pair);
			}
		}
	}

	for (int i = 0; i < size; i++) {
		int leaving = machine->getGraph()->getLeavingEdges(i)->size();
		int arriving = machine->getGraph()->getArrivingEdges(i)->size();

		if (leaving == 0 ) {
			if (arriving == 1) {
				machine->getGraph()->getNode(i)->getType()->changeContainerType(ContainerType::sink);
				machine->getGraph()->getNode(i)->getType()->changeMovementType(MovementType::irrelevant);
			}
			else if (arriving > 1) {
				machine->getGraph()->getNode(i)->getType()->changeContainerType(ContainerType::convergent_switch);
				machine->getGraph()->getNode(i)->getType()->changeMovementType(MovementType::irrelevant);
			}
			else {
				machine->getGraph()->getNode(i)->getType()->changeContainerType(ContainerType::unknow);
				machine->getGraph()->getNode(i)->getType()->changeMovementType(MovementType::irrelevant);
			}
		}
		else if (leaving == 1) {
			if (arriving == 1) {
				machine->getGraph()->getNode(i)->getType()->changeContainerType(ContainerType::flow);
			}
			else if (arriving > 1) {
				machine->getGraph()->getNode(i)->getType()->changeContainerType(ContainerType::convergent_switch_inlet);
			}
			else {
				machine->getGraph()->getNode(i)->getType()->changeContainerType(ContainerType::inlet);
			}
		}
		else if (leaving > 1) {
			if (arriving == 1) {
				machine->getGraph()->getNode(i)->getType()->changeContainerType(ContainerType::divergent_switch_sink);
			}
			else if (arriving > 1) {
				machine->getGraph()->getNode(i)->getType()->changeContainerType(ContainerType::bidirectional_switch);
			}
			else {
				machine->getGraph()->getNode(i)->getType()->changeContainerType(ContainerType::divergent_switch);
			}
		}
	}

	return machine;
}

ExecutableMachineGraph* Test::makeSimpleMachine(int communications, std::unique_ptr<CommandSender> exec, std::unique_ptr<CommandSender> test) {
	ExecutableMachineGraph* machine = new ExecutableMachineGraph(
		"simpleMachine", std::move(exec), std::move(test));

	std::shared_ptr<Control> control(new EvoprogSixwayValve(communications, 7));
	std::shared_ptr<Light> light(new EvoprogLight(communications, 2, 3));
	std::shared_ptr<Temperature> temperature(
		new EvoprogTemperature(communications, 1));
	std::shared_ptr<Extractor> cExtractor13(
		new EvoprogContinuousPump(communications, 13));
	std::shared_ptr<Extractor> cExtractor14(
		new EvoprogContinuousPump(communications, 14));
	std::shared_ptr<Extractor> dExtractor(
		new EvoprogDiscretePump(communications, 15));
	std::shared_ptr<Injector> dummyInjector(
		new EvoprogDummyInjector(communications));
	std::shared_ptr<ODSensor> od(new EvoprogOdSensor(communications, 4));

	ExecutableMachineGraph::ExecutableContainerNodePtr cInlet1 = std::make_shared<InletContainer>(1, 100.0, cExtractor13);
	cInlet1->setLight(light);
	ExecutableMachineGraph::ExecutableContainerNodePtr dInlet2 = std::make_shared<InletContainer>(2, 100.0, dExtractor);
	dInlet2->setTemperature(temperature);
	ExecutableMachineGraph::ExecutableContainerNodePtr cSwtInlet3 = std::make_shared<ConvergentSwitchInlet>(3, 100.0, dummyInjector, cExtractor14, control);
	cSwtInlet3->setOd(od);
	ExecutableMachineGraph::ExecutableContainerNodePtr sink = std::make_shared<SinkContainer>(4, 100.0, dummyInjector);

	machine->addContainer(cInlet1);
	machine->addContainer(dInlet2);
	machine->addContainer(cSwtInlet3);
	machine->addContainer(sink);

	machine->connectExecutableContainer(1, 3);
	machine->connectExecutableContainer(2, 3);
	machine->connectExecutableContainer(3, 4);

	return machine;
}

ExecutableMachineGraph* Test::makeMatrixMachine(int communications, std::unique_ptr<CommandSender> exec, std::unique_ptr<CommandSender> test,
	int size) {
	ExecutableMachineGraph* machine = new ExecutableMachineGraph(
		"matrixMachine", std::move(exec), std::move(test));

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			ExecutableMachineGraph::ExecutableContainerNodePtr node;
			if (i == 0) {
				if (j == 0) {
					std::shared_ptr<Injector> inject(new EvoprogDummyInjector(communications));
					std::shared_ptr<Control> ctrl(new EvoprogSixwayValve(communications, 3));
					node = std::make_shared<ConvergentSwitch>(i*size + j, 100.0, inject, ctrl);
				}
				else if (j == size - 1) {
					std::shared_ptr<Injector> inject(new EvoprogDummyInjector(communications));
					std::shared_ptr<Extractor> extract(new EvoprogContinuousPump(communications, 1));
					node = std::make_shared<FlowContainer>(i*size + j, 100.0, extract, inject);
				}
				else {
					std::shared_ptr<Injector> inject(new EvoprogDummyInjector(communications));
					std::shared_ptr<Extractor> extract(new EvoprogContinuousPump(communications, 1));
					std::shared_ptr<Control> ctrl(new EvoprogSixwayValve(communications, 3));
					node = std::make_shared<ConvergentSwitchInlet>(i*size + j, 100.0, inject, extract, ctrl);
				}
			}
			else if (i == size - 1) {
				if (j == 0) {
					std::shared_ptr<Injector> inject(new EvoprogDummyInjector(communications));
					std::shared_ptr<Extractor> extract(new EvoprogContinuousPump(communications, 1));
					node = std::make_shared<FlowContainer>(i * size + j, 100.0, extract, inject);
				}
				else if (j == size - 1) {
					std::shared_ptr<Extractor> extract(new EvoprogContinuousPump(communications, 1));
					std::shared_ptr<Control> ctrl(new EvoprogSixwayValve(communications, 3));
					node = std::make_shared<DivergentSwitch>(i*size + j, 100.0, extract, ctrl);
				}
				else {
					std::shared_ptr<Injector> inject(new EvoprogDummyInjector(communications));
					std::shared_ptr<Extractor> extract(new EvoprogContinuousPump(communications, 1));
					std::shared_ptr<Control> ctrl(new EvoprogSixwayValve(communications, 3));
					node = std::make_shared<DivergentSwitchSink>(i*size + j, 100.0, inject, extract, ctrl);
				}
			}
			else {
				if (j == 0) {
					std::shared_ptr<Injector> inject(new EvoprogDummyInjector(communications));
					std::shared_ptr<Extractor> extract(new EvoprogContinuousPump(communications, 1));
					std::shared_ptr<Control> ctrl(new EvoprogSixwayValve(communications, 3));
					node = std::make_shared<ConvergentSwitchInlet>(i*size + j, 100.0, inject, extract, ctrl);
				}
				else if (j == size - 1) {
					std::shared_ptr<Injector> inject(new EvoprogDummyInjector(communications));
					std::shared_ptr<Extractor> extract(new EvoprogContinuousPump(communications, 1));
					std::shared_ptr<Control> ctrl(new EvoprogSixwayValve(communications, 3));
					node = std::make_shared<DivergentSwitchSink>(i*size + j, 100.0, inject, extract, ctrl);
				}
				else {
					std::shared_ptr<Injector> inject(new EvoprogDummyInjector(communications));
					std::shared_ptr<Extractor> extract(new EvoprogContinuousPump(communications, 1));
					std::shared_ptr<Control> ctrlIn(new EvoprogSixwayValve(communications, 3));
					std::shared_ptr<Control> ctrlOut(new EvoprogSixwayValve(communications, 3));
					node = std::make_shared<BidirectionalSwitch>(i*size + j, 100.0, extract, inject, ctrlIn, ctrlOut);
				}
			}
			machine->addContainer(node);
			if (i > 0) {
				machine->connectExecutableContainer(i*size + j, (i - 1)*size + j);
			}

			if (j > 0) {
				machine->connectExecutableContainer(i*size + j, i*size + j - 1);
			}
		}
	}
	return machine;
}

void Test::testExecutableMachineGraphPerformance() {
	std::unique_ptr<CommandSender> comEx(new SerialSender("\\\\.\\COM3"));
	std::unique_ptr<CommandSender> comTest(new FileSender("test.log", "inputFileData.txt"));
	int communications = CommunicationsInterface::GetInstance()->addCommandSender(comEx->clone());

	LOG(INFO) << "creating machine...";
	ExecutableMachineGraph* machine = makeMatrixMachine(communications, std::move(comEx), std::move(comTest), 5);

	ContainerNodeType cinlet(MovementType::continuous, ContainerType::inlet);
	ContainerNodeType sink(MovementType::irrelevant, ContainerType::sink);

	LOG(INFO) << "printing graph...";
	machine->saveGraph("matrixMachine.graph");

	//LOG(INFO)<< "not available 2";
	//machine->addUsedNode(4);

	DWORD init = GetTickCount();
	LOG(INFO) << "getting flows inlet to sink...";
	std::priority_queue<Flow<Edge>, vector<Flow<Edge>>,
		FlowPtrComparator<Edge>> f = machine->getAvailableFlows(cinlet,
			sink, *(machine->getGraph()->getAllNodes()));
	DWORD end = GetTickCount();

	LOG(INFO) << "calculate " << f.size() << " flows, in " << ((end - init)) << " ms";

	LOG(INFO) << "destroying machine";
	delete machine;
}

void Test::testEvoprogComponents() {
	try {
		CommandSender* communications = new SerialSender("\\\\.\\COM3");
		int com = CommunicationsInterface::GetInstance()->addCommandSender(communications);

		Extractor* ext = new EvoprogContinuousPump(com, 2);
		ODSensor* od = new EvoprogOdSensor(com, 3);
		Light* light = new EvoprogLight(com, 4, 5);

		LOG(INFO) << "extracting liquid";
		ext->extractLiquid(1.0);

		LOG(INFO) << "reading sensor";
		LOG(INFO) << "read " << od->readOd();

		LOG(INFO) << "send light command...";
		light->applyLight(20.0, 50.0);

	}
	catch (std::ios_base::failure& e) {
		LOG(INFO) << "error: " << e.what();
	}
	catch (std::invalid_argument& e) {
		LOG(INFO) << "error: " << e.what();
	}
}

void Test::testCalculateSubgraphs() {
	Graph<Node, Edge>* g = new Graph<Node, Edge>();

	g->addNode(std::make_shared<Node>(1));
	g->addNode(std::make_shared<Node>(2));
	g->addNode(std::make_shared<Node>(3));
	g->addNode(std::make_shared<Node>(4));
	g->addNode(std::make_shared<Node>(5));
	g->addNode(std::make_shared<Node>(6));
	g->addNode(std::make_shared<Node>(7));
	g->addNode(std::make_shared<Node>(8));
	g->addNode(std::make_shared<Node>(9));
	g->addNode(std::make_shared<Node>(10));
	g->addNode(std::make_shared<Node>(11));

	g->addEdge(std::make_shared<Edge>(1, 2));
	g->addEdge(std::make_shared<Edge>(2, 3));
	//g->addEdge(std::make_shared<Edge>(2,4));
	g->addEdge(std::make_shared<Edge>(4, 5));
	g->addEdge(std::make_shared<Edge>(4, 6));
	g->addEdge(std::make_shared<Edge>(7, 8));
	g->addEdge(std::make_shared<Edge>(8, 9));
	g->addEdge(std::make_shared<Edge>(9, 10));
	g->addEdge(std::make_shared<Edge>(10, 11));

	Graph<Node, Edge>::SubGraphPtr subGraph = g->getSubGraphs();
	int color = 0;
	for (auto it = subGraph->begin(); it != subGraph->end(); ++it) {
		LOG(INFO) << "subGraph " << color << ": ";
		Graph<Node, Edge>::NodeVectorPtr actualSubgraph = get<0>(*it);
		for (auto it1 = actualSubgraph->begin(); it1 != actualSubgraph->end(); ++it1) {
			Graph<Node, Edge>::NodeTypePtr act = *it1;
			LOG(INFO) << act->toText();
		}
		color++;
	}
}

void Test::testContainerNodeType() {
	std::vector<ContainerNodeType> types;
	ContainerNodeType t1(MovementType::continuous, ContainerType::flow);
	types.push_back(t1);

	ContainerNodeType t2(MovementType::discrete, ContainerType::flow);

	LOG(INFO) << "is t1 == t2? 1: " << (t1 == t2);

	auto it = std::find(types.begin(), types.end(), t2);

	LOG(INFO) << "is t2 in types? 1: " << (it != types.end());
}

void Test::testCompatibleSubgraph() {
	std::tr1::unordered_set<int> used;
	std::vector<ContainerNode*> vect1;
	std::vector<ContainerNode*> vect2;

	ContainerNode* c1 = new ContainerNode(1,
		std::shared_ptr<ContainerNodeType>(
			new ContainerNodeType(MovementType::continuous,
				ContainerType::inlet)), 100.0);
	ContainerNode* c2 = new ContainerNode(2,
		std::shared_ptr<ContainerNodeType>(
			new ContainerNodeType(MovementType::continuous,
				ContainerType::flow)), 100.0);
	ContainerNode* c3 = new ContainerNode(3,
		std::shared_ptr<ContainerNodeType>(
			new ContainerNodeType(MovementType::irrelevant,
				ContainerType::sink)), 100.0);

	vect1.push_back(c1);
	vect1.push_back(c2);
	vect1.push_back(c3);

	ContainerNode* c4 = new ContainerNode(4,
		std::shared_ptr<ContainerNodeType>(
			new ContainerNodeType(MovementType::continuous,
				ContainerType::divergent_switch)), 100.0);
	ContainerNode* c5 = new ContainerNode(5,
		std::shared_ptr<ContainerNodeType>(
			new ContainerNodeType(MovementType::continuous,
				ContainerType::bidirectional_switch)), 100.0);
	ContainerNode* c6 = new ContainerNode(6,
		std::shared_ptr<ContainerNodeType>(
			new ContainerNodeType(MovementType::irrelevant,
				ContainerType::convergent_switch)), 100.0);
	vect2.push_back(c4);
	vect2.push_back(c5);
	vect2.push_back(c6);

	LOG(INFO) << "is 1 in v1 ? 1: " << ContainersUtils::isNodeInVector<ContainerNode>(1, vect1);
	LOG(INFO) << "is 1 in v2 ? 0: " << ContainersUtils::isNodeInVector<ContainerNode>(1, vect2);
	LOG(INFO) << "is c4 in v2 ? 1: " << ContainersUtils::isNodeInVector<ContainerNode, ContainerNode>(c4, vect2);
	LOG(INFO) << "is c4 in v1 ? 0: " << ContainersUtils::isNodeInVector<ContainerNode, ContainerNode>(c4, vect1);

	delete c1;
	delete c2;
	delete c3;
	delete c4;
	delete c5;
	delete c6;
}

ExecutableMachineGraph* Test::makeMappingMachine(int communications,
	std::unique_ptr<CommandSender> exec, std::unique_ptr<CommandSender> test) {

	ExecutableMachineGraph* machine = new ExecutableMachineGraph(
		"mappingMachine", std::move(exec), std::move(test));

	std::shared_ptr<Control> control(
		new EvoprogSixwayValve(communications, 7));
	std::shared_ptr<Extractor> cExtractor(
		new EvoprogContinuousPump(communications, 13));
	std::shared_ptr<Injector> dummyInjector(
		new EvoprogDummyInjector(communications));
	std::shared_ptr<ODSensor> sensor(new EvoprogOdSensor(communications, 14));

	ExecutableMachineGraph::ExecutableContainerNodePtr cInlet1 = std::make_shared<InletContainer>(1, 100.0, cExtractor);
	ExecutableMachineGraph::ExecutableContainerNodePtr cInlet2 = std::make_shared<DivergentSwitch>(2, 100.0, cExtractor, control);
	ExecutableMachineGraph::ExecutableContainerNodePtr cInlet3 = std::make_shared<FlowContainer>(3, 100.0, cExtractor, dummyInjector);
	ExecutableMachineGraph::ExecutableContainerNodePtr cInlet4 = std::make_shared<InletContainer>(4, 100.0, cExtractor);


	ExecutableMachineGraph::ExecutableContainerNodePtr cSwtInlet5 = std::make_shared<ConvergentSwitchInlet>(5, 100.0,
		dummyInjector, cExtractor, control);
	ExecutableMachineGraph::ExecutableContainerNodePtr cSwtInlet6 = std::make_shared<BidirectionalSwitch>(6, 100.0,
		cExtractor, dummyInjector, control, control);
	cSwtInlet6->setOd(sensor);
	ExecutableMachineGraph::ExecutableContainerNodePtr cSwich7 = std::make_shared<ConvergentSwitch>(7, 100.0, dummyInjector, control);

	machine->addContainer(cInlet1);
	machine->addContainer(cInlet2);
	machine->addContainer(cInlet3);
	machine->addContainer(cInlet4);
	machine->addContainer(cSwtInlet5);
	machine->addContainer(cSwtInlet6);
	machine->addContainer(cSwich7);

	machine->connectExecutableContainer(1, 5);
	machine->connectExecutableContainer(2, 5);
	machine->connectExecutableContainer(3, 6);
	machine->connectExecutableContainer(4, 6);
	machine->connectExecutableContainer(5, 7);
	machine->connectExecutableContainer(6, 7);
	machine->connectExecutableContainer(6, 2);
	machine->connectExecutableContainer(2, 3);

	return machine;
}

MachineGraph* Test::makeTurbidostatSketch() {
	MachineGraph* sketch = new MachineGraph("sketchTurbidostat");

	std::shared_ptr<ContainerNodeType> cinlet(new ContainerNodeType(MovementType::continuous, ContainerType::inlet));
	std::shared_ptr<ContainerNodeType> cFlow(new ContainerNodeType(MovementType::continuous, ContainerType::flow));
	std::shared_ptr<ContainerNodeType> sink(new ContainerNodeType(MovementType::irrelevant, ContainerType::sink));

	sketch->addContainer(1, cinlet, 100.0);
	sketch->addContainer(2, cFlow, 100.0);
	sketch->addContainer(3, sink, 100.0);

	sketch->connectContainer(1, 2);
	sketch->connectContainer(2, 3);

	return sketch;
}

void Test::testMappingEngine() {
	std::unique_ptr<CommandSender> comEx = std::unique_ptr<CommandSender>(new SerialSender("\\\\.\\COM3"));
	std::unique_ptr<CommandSender> comTest = std::unique_ptr<CommandSender>(new FileSender("test.log", "inputFileData.txt"));
	int com = CommunicationsInterface::GetInstance()->addCommandSender(comEx->clone());

	MachineGraph* sketch = makeTurbidostatSketch();
	std::shared_ptr<ExecutableMachineGraph> machine(makeMappingMachine(com, std::move(comEx), std::move(comTest)));
	MappingEngine* map = new MappingEngine(sketch, machine);

	sketch->printMachine("turbidostatSketch.graph");
	machine->saveGraph("mappingSimpleMachine.graph");

	LOG(INFO) << "edge list size" << sketch->getGraph()->getEdgeList()->size();
	LOG(INFO) << "making mapping... ";
	if (map->startMapping()) {
		LOG(INFO) << "edge list size" << sketch->getGraph()->getEdgeList()->size();

		const MachineGraph::ContainerEdgeVectorPtr edges = sketch->getGraph()->getEdgeList();
		const MachineGraph::ContainerNodeVectorPtr nodes = sketch->getGraph()->getAllNodes();

		for (auto it = nodes->begin(); it != nodes->end(); ++it) {
			MachineGraph::ContainerNodePtr act = *it;
			LOG(INFO) << " sketch : " << patch::to_string(act->getContainerId()) << ", machine: " << patch::to_string(map->getMappedContainerId(act->getContainerId()));
		}

		for (auto it = edges->begin(); it != edges->end(); ++it) {
			MachineGraph::ContainerEdgePtr act = *it;
			LOG(INFO) << " sketch : " << act->toText() << ", machine: " << map->getMappedEdge(act)->toText();
		}

		LOG(INFO) << "used Nodes:";
		ExecutableMachineGraph::UsedMapPtr usedNodes = machine->getUsedNodes();
		for (auto it = usedNodes->begin(); it != usedNodes->end(); ++it) {
			LOG(INFO) << *it;
		}
	}
	else {
		LOG(INFO) << "mapping error!";
	}

}

MachineGraph* Test::makeMatrixSketch(int size) {
	MachineGraph* sketch = new MachineGraph("sketchMatrix");

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::shared_ptr<ContainerNodeType> type;
			if (i == 0) {
				if (j == 0) {
					type = std::shared_ptr<ContainerNodeType>(
						new ContainerNodeType(MovementType::irrelevant,
							ContainerType::convergent_switch));

				}
				else if (j == size - 1) {
					type = std::shared_ptr<ContainerNodeType>(
						new ContainerNodeType(MovementType::continuous,
							ContainerType::flow));
				}
				else {
					type = std::shared_ptr<ContainerNodeType>(
						new ContainerNodeType(MovementType::continuous,
							ContainerType::convergent_switch_inlet));
				}
			}
			else if (i == size - 1) {
				if (j == 0) {
					type = std::shared_ptr<ContainerNodeType>(
						new ContainerNodeType(MovementType::continuous,
							ContainerType::flow));
				}
				else if (j == size - 1) {
					type = std::shared_ptr<ContainerNodeType>(
						new ContainerNodeType(MovementType::continuous,
							ContainerType::divergent_switch));
				}
				else {
					type = std::shared_ptr<ContainerNodeType>(
						new ContainerNodeType(MovementType::continuous,
							ContainerType::divergent_switch_sink));
				}
			}
			else {
				if (j == 0) {
					type = std::shared_ptr<ContainerNodeType>(
						new ContainerNodeType(MovementType::continuous,
							ContainerType::convergent_switch_inlet));
				}
				else if (j == size - 1) {
					type = std::shared_ptr<ContainerNodeType>(
						new ContainerNodeType(MovementType::continuous,
							ContainerType::divergent_switch_sink));
				}
				else {
					type = std::shared_ptr<ContainerNodeType>(
						new ContainerNodeType(MovementType::continuous,
							ContainerType::bidirectional_switch));
				}
			}
			sketch->addContainer(i * size + j, type, 100.0);
			if (i > 0) {
				sketch->connectContainer(i * size + j, (i - 1) * size + j);
			}

			if (j > 0) {
				sketch->connectContainer(i * size + j, i * size + j - 1);
			}
		}
	}
	return sketch;
}

void Test::testMappingEnginePerformance() {
	std::unique_ptr<CommandSender> comEx = std::unique_ptr<CommandSender>(new SerialSender("\\\\.\\COM3"));
	std::unique_ptr<CommandSender> comTest = std::unique_ptr<CommandSender>(new FileSender("test.log", "inputFileData.txt"));
	int com = CommunicationsInterface::GetInstance()->addCommandSender(comEx->clone());

	MachineGraph* sketch = makeMatrixSketch(4);
	std::shared_ptr<ExecutableMachineGraph> machine(makeMatrixMachine(com, std::move(comEx), std::move(comTest), 20));
	MappingEngine* map = new MappingEngine(sketch, machine);

	LOG(INFO) << "printing machine...";
	machine->saveGraph("mappingMachine.graph");
	sketch->printMachine("sketchMapping.graph");

	LOG(INFO) << "edge list size" << sketch->getGraph()->getEdgeList()->size();
	LOG(INFO) << "making mapping... ";
	DWORD init = GetTickCount();
	if (map->startMapping()) {
		DWORD end = GetTickCount();
		LOG(INFO) << "spend: " << ((end - init)) << " ms";

		LOG(INFO) << "edge list size" << sketch->getGraph()->getEdgeList()->size();

		const MachineGraph::ContainerEdgeVectorPtr edges = sketch->getGraph()->getEdgeList();
		const MachineGraph::ContainerNodeVectorPtr nodes = sketch->getGraph()->getAllNodes();

		unordered_set<int> set;
		for (auto it = nodes->begin(); it != nodes->end(); ++it) {
			MachineGraph::ContainerNodePtr act = *it;
			try {
				int nm = map->getMappedContainerId(act->getContainerId());
				if (set.find(nm) != set.end()) {
					LOG(FATAL) << "error " << nm << " used twice";
				} else {
					set.insert(nm);
				}

				LOG(INFO) << " sketch : " << patch::to_string(act->getContainerId()) << ", machine: " << patch::to_string(nm);
			}
			catch (std::invalid_argument & e) {
				LOG(INFO) << "exception " << e.what();
			}
		}

		for (auto it = edges->begin(); it != edges->end(); ++it) {

			try {
				LOG(INFO) << " sketch : " << (*it)->toText() << ", machine: " << map->getMappedEdge((*it))->toText();
			}
			catch (std::invalid_argument& e) {
				LOG(INFO) << "exception " << e.what();
			}
		}

		LOG(INFO) << "used Nodes:";
		ExecutableMachineGraph::UsedMapPtr usedNodes = machine->getUsedNodes();
		for (auto it = usedNodes->begin(); it != usedNodes->end(); ++it) {
			LOG(INFO) << *it;
		}
	}
	else {
		LOG(INFO) << "mapping cannot be done";
	}
}

void Test::testCommunicationsInterface() {
	CommunicationsInterface* com = CommunicationsInterface::GetInstance();

	int id1 = com->addCommandSender(new SerialSender("\\\\.\\COM3"));

	LOG(INFO) << "id1 = " << patch::to_string(id1);

	CommunicationsInterface* com2 = CommunicationsInterface::GetInstance();
	int id2 = com2->addCommandSender(new SerialSender("\\\\.\\COM3"));

	LOG(INFO) << "id2 = " << patch::to_string(id2);

	CommunicationsInterface::freeCommandInterface();
}

void Test::testFileCommandSender() {
	CommunicationsInterface::GetInstance()->setTesting(true);
	int id = CommunicationsInterface::GetInstance()->addCommandSender(new FileSender("test.log", "inputFileData.txt"));
	CommunicationsInterface::GetInstance()->getCommandSender(id)->connect();

	LOG(INFO) << "receiving strings";
	for (int i = 0; i < 40; i++) {
		CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(id);
		com->sendString("testing");
		Sleep(100);
		LOG(INFO) << com->readUntil('\n');
	}

	CommunicationsInterface::GetInstance()->getCommandSender(id)->disconnect();
	CommunicationsInterface::freeCommandInterface();
}

void Test::testMappingTest() {

	std::unique_ptr<CommandSender> test = std::unique_ptr<CommandSender>(new FileSender("test.log", "inputFileData.txt"));
	std::unique_ptr<CommandSender> exec = std::unique_ptr<CommandSender>(new SerialSender());

	std::vector<int> v;
	CommunicationsInterface::GetInstance()->setTesting(true);

	int idCom = CommunicationsInterface::GetInstance()->addCommandSender(test->clone());
	v.push_back(idCom);

	std::shared_ptr<ExecutableMachineGraph> exMachine(makeSimpleMachine(idCom, std::move(exec), std::move(test)));

	std::shared_ptr<VariableTable> t(new VariableTable());
	std::shared_ptr<Mapping> map(new Mapping(exMachine, "simpleMachine", v));
	std::shared_ptr<ProtocolGraph> protocol(MakeTurbidostat(t, map));

	LOG(INFO) << "printing graphs...";
	protocol->printProtocol("protocol");
	map->printSketch("sketch");
	exMachine->printMachine("machine");

	ExecutionEngine* evo = new ExecutionEngine(protocol, t, map);

	LOG(INFO) << "Executing test...";
	bool correct = evo->test();
	LOG(INFO) << "result: " << correct;
}

void Test::testMappingExec() {
	std::unique_ptr<CommandSender> test(new FileSender("test.log", "inputFileData.txt"));
	std::unique_ptr<CommandSender> exec(new SerialSender("\\\\.\\COM3"));

	CommunicationsInterface::GetInstance()->setTesting(false);
	int idCom = CommunicationsInterface::GetInstance()->addCommandSender(exec->clone());

	std::vector<int> v;
	v.push_back(idCom);

	std::shared_ptr<ExecutableMachineGraph> exMachine(makeSimpleMachine(idCom, std::move(exec), std::move(test)));

	std::shared_ptr<VariableTable> t(new VariableTable());
	std::shared_ptr<Mapping> map(new Mapping(exMachine, "simpleMachine", v));
	std::shared_ptr<ProtocolGraph> protocol(MakeTurbidostat(t, map));

	LOG(INFO) << "printing graphs...";
	protocol->printProtocol("protocol");
	map->printSketch("sketch");
	exMachine->printMachine("machine");

	ExecutionEngine* evo = new ExecutionEngine(protocol, t, map);

	LOG(INFO) << "Executing test...";
	bool correct = evo->exec_general();
	LOG(INFO) << "result: " << correct;
}

void Test::testSerializeNode() {
	{
		int communications = 0;
		std::shared_ptr<VariableEntry> ve = std::shared_ptr<VariableEntry>(new VariableEntry());
		std::shared_ptr<Control> control(
			new EvoprogSixwayValve(communications, 7));
		std::shared_ptr<Extractor> cExtractor(
			new EvoprogContinuousPump(communications, 13));
		std::shared_ptr<Injector> dummyInjector(
			new EvoprogDummyInjector(communications));
		std::shared_ptr<ODSensor> sensor(new EvoprogOdSensor(communications, 14));

		Node n(1);
		shared_ptr<Node> cn1 = make_shared<ContainerNode>(2, make_shared<ContainerNodeType>(MovementType::continuous, ContainerType::inlet), 100.0);

		BidirectionalSwitch bdw(2, 100.0, cExtractor, dummyInjector, control, control);
		bdw.setOd(sensor);
		shared_ptr<Node> ecn1 = make_shared<BidirectionalSwitch>(bdw);

		ofstream o("test.json");
		LOG(INFO) << "serializating...";
		try {
			cereal::JSONOutputArchive ar(o);
			ar(n, cn1, ecn1, ve);
		}
		catch (cereal::Exception & e) {
			LOG(FATAL) << "exception while serializating, " << e.what();
		}
	}
	{
		Node n(1);
		shared_ptr<Node> cn1;
		shared_ptr<Node> ecn1;
		std::shared_ptr<VariableEntry> ve;
		ifstream i("test.json");
		try {
			cereal::JSONInputArchive arIn(i);
			LOG(INFO) << "created archive...";
			arIn(n, cn1, ecn1, ve);
			LOG(INFO) << "node: " << n.toText();
			LOG(INFO) << "container node: " << cn1->toText();
			LOG(INFO) << "executable container node: " << ecn1->toText();
		}
		catch (cereal::Exception& e) {
			LOG(FATAL) << "exception while de-serializating, " << e.what();
		}
	}

}

void Test::testSerializeMachine() {
	std::unique_ptr<CommandSender> test(new FileSender("test.log", "inputFileData.txt"));
	std::unique_ptr<CommandSender> exec(new SerialSender("\\\\.\\COM3"));

	int idCom = CommunicationsInterface::GetInstance()->addCommandSender(test->clone());
	std::vector<int> v;
	v.push_back(idCom);

	std::shared_ptr<MachineGraph> m = std::shared_ptr<MachineGraph>(makeTurbidostatSketch());
	std::shared_ptr<ExecutableMachineGraph> ex_m = std::shared_ptr<ExecutableMachineGraph>(makeMappingMachine(0, std::move(exec), std::move(test)));

	std::shared_ptr<VariableTable> t(new VariableTable());
	std::shared_ptr<Mapping> map(new Mapping(ex_m, "simpleMachine", v));
	std::shared_ptr<ProtocolGraph> p = std::shared_ptr<ProtocolGraph>(makeTimeProtocol(t, map));

	m->printMachine("preserializationMachine.graph");
	ex_m->printMachine("preserializationExMachine.graph");
	p->printProtocol("preserializeProtocol.graph");

	try {
		MachineGraph::toJSON("sketch.json", *(m.get()));
		ExecutableMachineGraph::toJSON("mappingMachine.json", *(ex_m.get()));
		ProtocolGraph::toJSON("protocol.json", *(p.get()));

		MachineGraph::fromJSON("sketch.json")->printMachine("postserializationMachine.graph");
		ExecutableMachineGraph::fromJSON("mappingMachine.json")->printMachine("postserializationExMachine.graph");
		ProtocolGraph::fromJSON("protocol.json")->printProtocol("postserializationProtocol.graph");
	}
	catch (cereal::Exception & e) {
		LOG(ERROR) << "exception, " << e.what();
	}
}

ProtocolGraph* Test::makeTimeProtocol(
	std::shared_ptr<VariableTable> table,
	std::shared_ptr<Mapping> map) {

	AutoEnumerate serial;
	ProtocolGraph* protocol = new ProtocolGraph("simpleProtocol");

	std::shared_ptr<ComparisonOperable> tautology(new Tautology());
	std::shared_ptr<MathematicOperable> num1(new ConstantNumber(0.001));
	std::shared_ptr<MathematicOperable> num60000(new ConstantNumber(60000));
	std::shared_ptr<MathematicOperable> num65(new ConstantNumber(65));

	ProtocolGraph::ProtocolNodePtr op1 = std::make_shared<LoadContainerOperation>(serial.getNextValue(), 1, num65); //loadContainer(1, 1000ml)

	protocol->addOperation(op1);

	std::shared_ptr<VariableEntry> time(
		new VariableEntry(TIME_VARIABLE));
	std::shared_ptr<MathematicOperable> mtime(
		new VariableEntry(TIME_VARIABLE));
	std::shared_ptr<ComparisonOperable> comp2in(
		new SimpleComparison(false, mtime, comparison::less_equal, num60000));
	ProtocolGraph::ProtocolNodePtr loop1 = std::make_shared<LoopNode>(serial.getNextValue(), comp2in); //while ( t <= 60s)

	protocol->addOperation(loop1);
	protocol->connectOperation(op1, loop1, tautology);

	ProtocolGraph::ProtocolNodePtr op2 = std::make_shared<SetContinousFlow>(serial.getNextValue(), 1, 2, num1);
	ProtocolGraph::ProtocolNodePtr op3 = std::make_shared<SetContinousFlow>(serial.getNextValue(), 2, 3, num1);

	protocol->addOperation(op2);
	protocol->connectOperation(loop1, op2, comp2in);
	protocol->addOperation(op3);
	protocol->connectOperation(op2, op3, tautology);
	ProtocolGraph::ProtocolNodePtr timeStep = std::make_shared<TimeStep>(serial.getNextValue(), time);

	protocol->addOperation(timeStep);
	protocol->connectOperation(op3, timeStep, tautology);
	protocol->connectOperation(timeStep, loop1, tautology);

	protocol->setStartNode(op1->getContainerId());
	return protocol;
}

void Test::testTimeStep() {
	std::unique_ptr<CommandSender> test(new FileSender("test.log", "inputFileData.txt"));
	std::unique_ptr<CommandSender> exec(new SerialSender("\\\\.\\COM3"));

	CommunicationsInterface::GetInstance()->setTesting(false);
	int idCom = CommunicationsInterface::GetInstance()->addCommandSender(exec->clone());

	std::vector<int> v;
	v.push_back(idCom);

	std::shared_ptr<ExecutableMachineGraph> exMachine(makeSimpleMachine(idCom, std::move(exec), std::move(test)));

	std::shared_ptr<VariableTable> t(new VariableTable());
	std::shared_ptr<Mapping> map(new Mapping(exMachine, "simpleMachine", v));
	std::shared_ptr<ProtocolGraph> protocol(makeTimeProtocol(t, map));

	LOG(INFO) << "printing graphs...";
	protocol->printProtocol("protocol");
	map->printSketch("sketch");
	exMachine->printMachine("machine");

	ExecutionEngine* evo = new ExecutionEngine(protocol, t, map);

	LOG(INFO) << "Executing test...";
	bool correct = evo->exec_general();
	LOG(INFO) << "result: " << correct;
}

void Test::testTimeStepTest() {
	std::unique_ptr<CommandSender> test(new FileSender("test.log", "inputFileData.txt"));
	std::unique_ptr<CommandSender> exec(new SerialSender("\\\\.\\COM3"));

	CommunicationsInterface::GetInstance()->setTesting(true);

	int idCom = CommunicationsInterface::GetInstance()->addCommandSender(test->clone());
	std::vector<int> v;
	v.push_back(idCom);

	std::shared_ptr<ExecutableMachineGraph> exMachine(makeSimpleMachine(idCom, std::move(exec), std::move(test)));

	std::shared_ptr<VariableTable> t(new VariableTable());
	std::shared_ptr<Mapping> map(new Mapping(exMachine, "simpleMachine", v));
	std::shared_ptr<ProtocolGraph> protocol(makeTimeProtocol(t, map));

	LOG(INFO) << "printing graphs...";
	protocol->printProtocol("protocol");
	map->printSketch("sketch");
	exMachine->printMachine("machine");

	ExecutionEngine* evo = new ExecutionEngine(protocol, t, map);

	LOG(INFO) << "Executing test...";
	bool correct = evo->test();
	LOG(INFO) << "result: " << correct;

	delete evo;
}

void Test::testSerializaVariableTable() {

	VariableTable v;

	v.setValue("uno", 1);
	v.setValue("dos", 2);
	v.setValue("tres", 3);
	v.setPhysical("tres", true);
	{
		ofstream o("test.json");
		LOG(INFO) << "serializating...";
		cereal::JSONOutputArchive ar(o);
		ar(v);
	}

	testDeserializaVariableTable("");
}

void Test::testDeserializaVariableTable(const std::string & json) {
	LOG(INFO) << "deserializating...";
	VariableTable v;
	{
		ifstream i("test.json");
		cereal::JSONInputArchive arIn(i);
		LOG(INFO) << "created archive...";
		arIn(v);
	}

	LOG(INFO) << "uno: " << v.getVaue("uno") << ", " << v.getPhysical("uno");
	LOG(INFO) << "dos: " << v.getVaue("dos") << ", " << v.getPhysical("dos");
	LOG(INFO) << "tres: " << v.getVaue("tres") << ", " << v.getPhysical("tres");

}

void Test::testSerialize_MathematicOperable() {

	{
		vector<shared_ptr<MathematicOperable>> v;

		shared_ptr<MathematicOperable> cn3(new ConstantNumber(3));
		shared_ptr<MathematicOperable> cn5(new ConstantNumber(5));
		shared_ptr<MathematicOperable> opPlus(
			new ArithmeticOperation(cn3, arithmetic::plus, cn5));
		shared_ptr<MathematicOperable> fabs5(
			new UnaryOperation(opPlus, unaryOperations::absoluteValue));

		v.push_back(cn3);
		v.push_back(cn5);
		v.push_back(opPlus);
		v.push_back(fabs5);

		ofstream o("test.json");
		LOG(INFO) << "serializating...";
		cereal::JSONOutputArchive ar(o);
		ar(CEREAL_NVP(v));
	}

	{
		vector<shared_ptr<MathematicOperable>> v;
		ifstream i("test.json");
		cereal::JSONInputArchive arIn(i);
		LOG(INFO) << "created archive...";
		arIn(v);

		for (auto it = v.begin(); it != v.end(); ++it) {
			LOG(INFO) << it->get()->toString();
		}
	}
}

void Test::testSerialize_ExecutableConatinerNode() {
	CommunicationsInterface::GetInstance()->setTesting(true);
	int communications =
		CommunicationsInterface::GetInstance()->addCommandSender(
			new FileSender("test.log", "inputFileData.txt"));

	shared_ptr<Control> control(new EvoprogSixwayValve(communications, 7));
	shared_ptr<Light> light(new EvoprogLight(communications, 2, 3));
	shared_ptr<Temperature> temperature(
		new EvoprogTemperature(communications, 1));
	shared_ptr<Extractor> cExtractor13(
		new EvoprogContinuousPump(communications, 13));
	shared_ptr<Extractor> cExtractor14(
		new EvoprogContinuousPump(communications, 14));
	shared_ptr<Extractor> dExtractor(
		new EvoprogDiscretePump(communications, 15));
	shared_ptr<Injector> dummyInjector(
		new EvoprogDummyInjector(communications));
	shared_ptr<ODSensor> od(new EvoprogOdSensor(communications, 4));

	shared_ptr<ExecutableContainerNode> cInlet1(
		new InletContainer(1, 100.0, cExtractor13));
	cInlet1->setLight(light);
	shared_ptr<ExecutableContainerNode> dInlet2(
		new InletContainer(2, 100.0, dExtractor));
	dInlet2->setTemperature(temperature);
	shared_ptr<ExecutableContainerNode> cSwtInlet3(
		new ConvergentSwitchInlet(3, 100.0, dummyInjector, cExtractor14,
			control));
	cSwtInlet3->setOd(od);
	shared_ptr<ExecutableContainerNode> sink(
		new SinkContainer(4, 100.0, dummyInjector));

	{
		vector<shared_ptr< ExecutableContainerNode>> v;
		v.push_back(cInlet1);
		v.push_back(dInlet2);
		v.push_back(cSwtInlet3);
		v.push_back(sink);

		ofstream o("test.json");
		LOG(INFO) << "serializating...";
		cereal::JSONOutputArchive ar(o);
		ar(CEREAL_NVP(v));
	}

	{
		vector<shared_ptr<ExecutableContainerNode>> v;
		ifstream i("test.json");
		cereal::JSONInputArchive arIn(i);
		LOG(INFO) << "created archive...";
		arIn(v);

		for (auto it = v.begin(); it != v.end(); ++it) {
			LOG(INFO) << it->get()->toText();
		}
	}
}

void Test::pythonTest() {

	using namespace boost::python;

	Chorra* cho = new Chorra(3);
	try {
		Py_Initialize();

		initChorraMod();

		object main_module = import("__main__");
		object main_namespace = main_module.attr("__dict__");

		std::string dir = Utils::getCurrentDir() + "\\plugins";
		LOG(INFO) << dir;

		//Add plugins folder to the python path
		PyObject* sysPath = PySys_GetObject("path");
		PyList_Insert(sysPath, 0, PyString_FromString(dir.c_str()));

		object rand_mod = import("random");

		object test = import("test");
		double randNum = extract<double>(rand_mod.attr("random")());

		main_namespace["var1"] = test.attr("Test")("Angel");
		main_namespace["var2"] = test.attr("Test")("Elena");

		main_namespace["var1"].attr("saluda")(ptr(cho));
		main_namespace["var2"].attr("saluda")(ptr(cho));

		cho->i = 5;

		main_namespace["var1"].attr("saluda")(ptr(cho));
		main_namespace["var2"].attr("saluda")(ptr(cho));

		//LOG(INFO) << extract<double>(rand_mod.attr("random")());


		/*exec("import random", main_namespace);
		object rand = eval("random.random()", main_namespace);
		std::cout << extract<double>(rand) << std::endl;*/

		Py_Finalize();
	}
	catch (error_already_set) {
		PyErr_Print();
	}
	delete cho;
}

void Test::testPythonEnvironment() {
	Chorra* cho = new Chorra(3);

	PluginFileLoader::GetInstance()->toText();

	PythonEnvironment::GetInstance()->initEnvironment();

	initChorraMod();

	try {
		vector<string> params1{ "Angel" };
		vector<string> params2{ "Elena" };

		LOG(INFO) << "making instance Test var1";
		string nv1 = PythonEnvironment::GetInstance()->makeInstance("Test", params1);
		LOG(INFO) << "making instance Test var2";
		string nv2 = PythonEnvironment::GetInstance()->makeInstance("Test", params2);

		LOG(INFO) << "executing saluda 3, nv1";
		PythonEnvironment::GetInstance()->getVarInstance(nv1).attr("saluda")(boost::python::ptr(cho));
		LOG(INFO) << "executing saluda 3, nv2";
		PythonEnvironment::GetInstance()->getVarInstance(nv2).attr("saluda")(boost::python::ptr(cho));

		cho->i = 5;

		LOG(INFO) << "executing saluda 5, nv1";
		PythonEnvironment::GetInstance()->getVarInstance(nv1).attr("saluda")(boost::python::ptr(cho));
		LOG(INFO) << "executing saluda 5, nv2";
		PythonEnvironment::GetInstance()->getVarInstance(nv2).attr("saluda")(boost::python::ptr(cho));
	}
	catch (std::invalid_argument & e) {
		LOG(ERROR) << e.what();
	}

	PythonEnvironment::GetInstance()->finishEnvironment();
}

void Test::pluinLoaderTest() {
	PluginFileLoader::GetInstance()->toText();
}

void Test::testOdSensorPlugin() {
	CommandSender* com = new FileSender("test.log", "inputFileData.txt");
	com->connect();
	int idCom = CommunicationsInterface::GetInstance()->addCommandSender(com);

	PythonEnvironment::GetInstance()->initEnvironment();

	vector<string> params{ "13" };
	ODSensorPlugin* od = new ODSensorPlugin(idCom, "EvoprogOdSensor", params);

	try {
		for (int i = 0; i < 20; i++) {
			LOG(INFO) << od->readOd();
		}
	}
	catch (std::runtime_error & e) {
		LOG(ERROR) << e.what();
	}

	com->disconnect();
	PythonEnvironment::GetInstance()->finishEnvironment();
}

ExecutableMachineGraph* Test::makeSimpleMachinePlugin(int communications, std::unique_ptr<CommandSender> exec, std::unique_ptr<CommandSender> test) {
	ExecutableMachineGraph* machine = new ExecutableMachineGraph(
		"simpleMachine", std::move(exec), std::move(test));

	vector<string> paramsc{ "7" };
	std::shared_ptr<Control> control(new ControlPlugin(communications, 6, "EvoprogSixWayValve", paramsc));

	vector<string> paramsl{ "3" };
	std::shared_ptr<Light> light(new LightPlugin(communications, "EvoprogLight", paramsl));

	vector<string> paramst{ "1" };
	std::shared_ptr<Temperature> temperature(
		new TemperaturePlugin(communications, "EvoprogTemperature", paramst));

	vector<string> paramsce{ "13" };
	std::shared_ptr<Extractor> cExtractor13(
		new ExtractorPlugin(communications, "EvoprogContinuousPump", paramsce));

	vector<string> paramsce2{ "14" };
	std::shared_ptr<Extractor> cExtractor14(
		new ExtractorPlugin(communications, "EvoprogContinuousPump", paramsce2));

	vector<string> paramsde{ "14" };
	std::shared_ptr<Extractor> dExtractor(
		new ExtractorPlugin(communications, "EvoprogDiscretePump", paramsde));

	vector<string> paramsdi;
	std::shared_ptr<Injector> dummyInjector(
		new InjectorPlugin(communications, "EvoprogDummyInjector", paramsdi));

	vector<string> paramsod{ "4" };
	std::shared_ptr<ODSensor> od(new ODSensorPlugin(communications, "EvoprogOdSensor", paramsod));

	ExecutableMachineGraph::ExecutableContainerNodePtr cInlet1 = std::make_shared<InletContainer>(1, 100.0, cExtractor13);
	cInlet1->setLight(light);
	ExecutableMachineGraph::ExecutableContainerNodePtr dInlet2 = std::make_shared<InletContainer>(2, 100.0, dExtractor);
	dInlet2->setTemperature(temperature);
	ExecutableMachineGraph::ExecutableContainerNodePtr cSwtInlet3 = std::make_shared<ConvergentSwitchInlet>(3, 100.0, dummyInjector, cExtractor14, control);
	cSwtInlet3->setOd(od);
	ExecutableMachineGraph::ExecutableContainerNodePtr sink = std::make_shared<SinkContainer>(4, 100.0, dummyInjector);

	machine->addContainer(cInlet1);
	machine->addContainer(dInlet2);
	machine->addContainer(cSwtInlet3);
	machine->addContainer(sink);

	machine->connectExecutableContainer(1, 3);
	machine->connectExecutableContainer(2, 3);
	machine->connectExecutableContainer(3, 4);

	return machine;
}

void Test::testMappingPluginTest() {
	PythonEnvironment::GetInstance()->initEnvironment();

	CommunicationsInterface::GetInstance()->setTesting(true);

	std::unique_ptr<CommandSender> test(new FileSender("test.log", "inputFileData.txt"));
	std::unique_ptr<CommandSender> exec(new SerialSender("\\\\.\\COM3"));

	int idCom = CommunicationsInterface::GetInstance()->addCommandSender(test->clone());
	std::vector<int> v;
	v.push_back(idCom);

	std::shared_ptr<ExecutableMachineGraph> exMachine(makeSimpleMachinePlugin(idCom, std::move(exec), std::move(test)));

	std::shared_ptr<VariableTable> t(new VariableTable());
	std::shared_ptr<Mapping> map(new Mapping(exMachine, "simpleMachine", v));
	std::shared_ptr<ProtocolGraph> protocol(MakeTurbidostat(t, map));

	LOG(INFO) << "printing graphs...";
	protocol->printProtocol("protocol");
	map->printSketch("sketch");
	exMachine->printMachine("machine");

	ExecutionEngine* evo = new ExecutionEngine(protocol, t, map);

	LOG(INFO) << "Executing test...";
	bool correct = evo->test();
	LOG(INFO) << "result: " << correct;
	PythonEnvironment::GetInstance()->finishEnvironment();
}

void Test::testMappingPluginExec() {
	PythonEnvironment::GetInstance()->initEnvironment();

	CommunicationsInterface::GetInstance()->setTesting(false);

	std::unique_ptr<CommandSender> test(new FileSender("test.log", "inputFileData.txt"));
	std::unique_ptr<CommandSender> exec(new SerialSender("\\\\.\\COM3"));

	int idCom = CommunicationsInterface::GetInstance()->addCommandSender(exec->clone());

	std::vector<int> v;
	v.push_back(idCom);

	std::shared_ptr<ExecutableMachineGraph> exMachine(makeSimpleMachinePlugin(idCom, std::move(exec), std::move(test)));

	std::shared_ptr<VariableTable> t(new VariableTable());
	std::shared_ptr<Mapping> map(new Mapping(exMachine, "simpleMachine", v));
	std::shared_ptr<ProtocolGraph> protocol(MakeTurbidostat(t, map));

	LOG(INFO) << "printing graphs...";
	protocol->printProtocol("protocol");
	map->printSketch("sketch");
	exMachine->printMachine("machine");

	ExecutionEngine* evo = new ExecutionEngine(protocol, t, map);

	LOG(INFO) << "Executing test...";
	bool correct = evo->exec_general();
	LOG(INFO) << "result: " << correct;

	PythonEnvironment::GetInstance()->finishEnvironment();
}

void Test::testExecutionServer() {
	PythonEnvironment::GetInstance()->initEnvironment();

	ExecutionServer* server = ExecutionServer::GetInstance();
	std::unique_ptr<CommandSender> test(new FileSender("test.log", "inputFileData.txt"));
	std::unique_ptr<CommandSender> exec(new SerialSender("\\\\.\\COM3"));

	LOG(INFO) << "making machine...";
	std::shared_ptr<ExecutableMachineGraph> exMachine(makeSimpleMachinePlugin(0, std::move(exec), std::move(test)));
	ExecutableMachineGraph::toJSON("exMachine.json", *exMachine.get());

	LOG(INFO) << "making turbidostat protocol...";
	std::vector<int> v;
	std::shared_ptr<VariableTable> t(new VariableTable());
	std::shared_ptr<Mapping> map(new Mapping(exMachine, "simpleMachine", v));
	std::shared_ptr<ProtocolGraph> protocol(makeTimeProtocol(t, map));
	ProtocolGraph::toJSON("tubidostat.json", *protocol.get());

	try {
		LOG(INFO) << "add new machine...";
		string machineRef = ExecutionMachineServer::GetInstance()->addNewMachine("exMachine.json");

		LOG(INFO) << "add protocol on new machine";
		string ref1 = server->addProtocolOnNewMachine("tubidostat.json", "exMachine.json");
		LOG(INFO) << "add protocol on existing machine";
		string ref2 = server->addProtocolOnExistingMachine("tubidostat.json", machineRef);

		LOG(INFO) << "test ref1";
		server->test(ref1);
		LOG(INFO) << "test ref2";
		server->exec(ref2);


		LOG(INFO) << "availables machines...";
		auto vec = ExecutionMachineServer::GetInstance()->getMachineMap();
		for (auto it = vec->begin(); it != vec->end(); ++it) {
			LOG(INFO) << it->first << " , " << get<1>(it->second)->getName();
		}
	}
	catch (std::runtime_error & e) {
		LOG(ERROR) << e.what();
	}
	catch (std::invalid_argument & e) {
		LOG(ERROR) << e.what();
	}

	ExecutionServer::freeCommandInterface();
	ExecutionMachineServer::freeCommandInterface();
	CommunicationsInterface::freeCommandInterface();

	PythonEnvironment::GetInstance()->finishEnvironment();
}

void Test::testFlowCalculatorIntensive() {

	std::unique_ptr<CommandSender> comEx(new SerialSender("\\\\.\\COM3"));
	std::unique_ptr<CommandSender> comTest(new FileSender("test.log", "inputFileData.txt"));
	int communications = CommunicationsInterface::GetInstance()->addCommandSender(comEx->clone());

	int size = 20;

	LOG(INFO) << "creating machine...";
	std::shared_ptr<ExecutableMachineGraph> machine = std::shared_ptr<ExecutableMachineGraph>(makeRandomMachine(std::move(comEx), std::move(comTest), size));

	LOG(INFO) << "printing machine...";
	machine->printMachine("random.graph");

	try {
		PathManager manger(machine);
		bool todoIgual = true;
		for (int i = 0; i < size; i++) {
			LOG(INFO) << "calculating flows" << i << " recursive way...";
			vector<std::shared_ptr<Flow<Edge>>> v1 = machine->getAllFlows(i, false);

			LOG(INFO) << "calculating flows " << i << " dynamic way...";
			shared_ptr<PathSearcherIterator> it = manger.getPathSearcher(i, false);
			vector<Flow<Edge>> v2;

			int p = 0;
			while (it->hasNext() != -1) {
				shared_ptr<Flow<Edge>> n = it->next();
				//std::string text = n->toText();
				//LOG(INFO) <<p;
				v2.push_back(*(n.get()));
				p++;
			}

			bool igual = v1.size() == v2.size();
			todoIgual = todoIgual && igual;
			LOG(INFO) << "nº flows equal: " << (igual) << ", " << v1.size() << ":" << v2.size();
			//LOG(INFO) << "n flows: " << n;
		}
		LOG(INFO) << "todos iguales = " << todoIgual;

		
		for (int i = 0; i < size; i++) {
			LOG(INFO) << "calculating reverse flows" << i << " recursive way...";
			vector<std::shared_ptr<Flow<Edge>>> v1 = machine->getAllFlows(i, true);

			LOG(INFO) << "calculating reverse flows " << i << " dynamic way...";
			shared_ptr<PathSearcherIterator> it = manger.getPathSearcher(i, true);
			vector<Flow<Edge>> v2;
			
			int p = 0;
			while (it->hasNext() != -1) {
				shared_ptr<Flow<Edge>> n = it->next();
				//std::string text = n->toText();
				//LOG(INFO) << p;
				v2.push_back(*(n.get()));
				p++;
			}

			bool igual = v1.size() == v2.size();
			todoIgual = todoIgual && igual;
			LOG(INFO) << "nº reverse flows equal: " << (igual) << ", " << v1.size() << ":" << v2.size();
			//LOG(INFO) << "n flows: " << n;
		}
		LOG(INFO) << "todos iguales reverse = " << todoIgual;
	}
	catch (exception & e) {
		LOG(ERROR) << e.what();
	}
}

void Test::testPathManager() {

	std::unique_ptr<CommandSender> comEx(new SerialSender("\\\\.\\COM3"));
	std::unique_ptr<CommandSender> comTest(new FileSender("test.log", "inputFileData.txt"));
	int communications = CommunicationsInterface::GetInstance()->addCommandSender(comEx->clone());

	int size = 5;

	LOG(INFO) << "creating machine...";
	std::shared_ptr<ExecutableMachineGraph> machine = std::shared_ptr<ExecutableMachineGraph>(makeMappingMachine(communications, std::move(comEx), std::move(comTest)));

	PathManager manager(machine);

	LOG(INFO) << " flows from 2 to 7..";

	shared_ptr<SearcherIterator> it = manager.getFlows(2, 7);

	while (it->hasNext()) {
		LOG(INFO) << it->next()->toText();
	}

	LOG(INFO) << " flows from 2 to sink..";

	it = manager.getFlows(2, make_shared<ContainerNodeType>(MovementType::irrelevant, ContainerType::sink));

	while (it->hasNext()) {
		LOG(INFO) << it->next()->toText();
	}

	LOG(INFO) << " flows from inlet to 7..";

	it = manager.getFlows(make_shared<ContainerNodeType>(MovementType::continuous, ContainerType::inlet), 7);

	while (it->hasNext()) {
		LOG(INFO) << it->next()->toText();
	}

	LOG(INFO) << " flows from inlet to sink..";

	it = manager.getFlows(make_shared<ContainerNodeType>(MovementType::continuous, ContainerType::inlet), make_shared<ContainerNodeType>(MovementType::irrelevant, ContainerType::sink));

	while (it->hasNext()) {
		LOG(INFO) << it->next()->toText();
	}

	LOG(INFO) << "reverse from 7, recursive...";
	vector<std::shared_ptr<Flow<Edge>>> v = machine->getAllFlows(7, true);

	for (auto it = v.begin(); it != v.end(); ++it) {
		LOG(INFO) << (*it)->toText();
	}
}

void Test::testMappingIntensive() {
	std::unique_ptr<CommandSender> comEx(new SerialSender("\\\\.\\COM3"));
	std::unique_ptr<CommandSender> comTest(new FileSender("test.log", "inputFileData.txt"));
	int communications = CommunicationsInterface::GetInstance()->addCommandSender(comEx->clone());

	int size = 200;

	LOG(INFO) << "creating machine...";
	std::shared_ptr<ExecutableMachineGraph> machine = std::shared_ptr<ExecutableMachineGraph>(makeRandomMachine(std::move(comEx), std::move(comTest), size));

	LOG(INFO) << "printing machine...";
	machine->printMachine("random.graph");

	MachineGraph* sketch = makeTurbidostatSketch();
	MappingEngine* map = new MappingEngine(sketch, machine);

	sketch->printMachine("turbidostatSketch.graph");
	machine->saveGraph("mappingSimpleMachine.graph");

	LOG(INFO) << "edge list size" << sketch->getGraph()->getEdgeList()->size();
	LOG(INFO) << "making mapping... ";
	if (map->startMapping()) {

		LOG(INFO) << "edge list size" << sketch->getGraph()->getEdgeList()->size();

		const MachineGraph::ContainerEdgeVectorPtr edges = sketch->getGraph()->getEdgeList();
		const MachineGraph::ContainerNodeVectorPtr nodes = sketch->getGraph()->getAllNodes();

		for (auto it = nodes->begin(); it != nodes->end(); ++it) {
			MachineGraph::ContainerNodePtr act = *it;
			LOG(INFO) << " sketch : " << patch::to_string(act->getContainerId()) << ", machine: " << patch::to_string(map->getMappedContainerId(act->getContainerId()));
		}

		for (auto it = edges->begin(); it != edges->end(); ++it) {
			MachineGraph::ContainerEdgePtr act = *it;
			LOG(INFO) << " sketch : " << act->toText() << ", machine: " << map->getMappedEdge(act)->toText();
		}

		LOG(INFO) << "used Nodes:";
		ExecutableMachineGraph::UsedMapPtr usedNodes = machine->getUsedNodes();
		for (auto it = usedNodes->begin(); it != usedNodes->end(); ++it) {
			LOG(INFO) << *it;
		}
	}
	else {
		LOG(INFO) << "mapping error!";
	}


}