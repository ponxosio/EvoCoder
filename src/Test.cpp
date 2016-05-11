/*
 * Test.cpp
 *
 *  Created on: 3 de mar. de 2016
 *      Author: angel
 */

#include "Test.h"

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

	LOG(INFO)<< "started!...";

	/*t.testGraph();
	 t.testContainerNode();
	 t.testVariableTable();
	 t.testComparisonVariable();
	 t.testComparisonVariable();
	 */
//	boost::shared_ptr<VariableTable> table(new VariableTable());
//	t.testVariableTable(table, "wikiwiki");
//	t.testMathematicVariable();
	//t.testUnaryOperation();
	//t.testSketcher();
	//t.testMapping();
	//t.testFlow();
	t.testExecutableMachineGraph();

	//t.testSerialPort_send();

	//t.testSerialPort_receive();

	LOG(INFO)<< "finished!";
}

void Test::testGraph() {
	Graph<Node, Edge>* g = new Graph<Node, Edge>();

	if (g->addNode(new Node(0)) && g->addNode(new Node(1))
			&& g->addNode(new Node(2)) && g->addEdge(new Edge(0, 1))
			&& g->addEdge(new Edge(1, 2)) && g->saveGraph("test.graph")) {
	} else {
		LOG(ERROR)<< "error creating and saving graph";
	}

	LOG(DEBUG)<< "vecinos(0) 1 : " << g->getNeighbors(0)->size();

	Graph<Node, Edge>* loadG = Graph<Node, Edge>::loadGraph(
			"X:\\codigo\\EvoCoder_Release_v1\\EvoCoder\\test.graph");
	if ((loadG != NULL)) {
		LOG(DEBUG)<< "Grafo cargado..." << endl;
		LOG(DEBUG) << loadG->toString() << endl;

		loadG->removeNode(0);
		LOG(DEBUG) << "Grafo: borrar nodo 0..." << endl;
		LOG(DEBUG) << loadG->toString() << endl;

		Edge tempE(1,2);
		loadG->removeEdge(tempE);
		LOG(DEBUG) << "Grafo: borrar arista 1->2..." << endl;
		LOG(DEBUG) << loadG->toString() << endl;

	} else {
		LOG(ERROR) << "error loading graph";
	}
	delete loadG;
	delete g;

}

void Test::testContainerNode() {
	Graph<ContainerNode, Edge>* g = new Graph<ContainerNode, Edge>();

	if (g->addNode(
			new ContainerNode(0,
					boost::shared_ptr<ContainerNodeType>(
							new ContainerNodeType(MovementType::continuous,
									ContainerType::inlet)), 10.0f))
			&& g->addNode(
					new ContainerNode(1,
							boost::shared_ptr<ContainerNodeType>(
									new ContainerNodeType(
											MovementType::continuous,
											ContainerType::flow)), 10.0f))
			&& g->addNode(
					new ContainerNode(2,
							boost::shared_ptr<ContainerNodeType>(
									new ContainerNodeType(
											MovementType::irrelevant,
											ContainerType::sink)), 10.0f))
			&& g->addEdge(new Edge(0, 1)) && g->addEdge(new Edge(1, 2))
			&& g->saveGraph("test_container.graph")) {
	} else {
		LOG(ERROR)<< "error creating and saving graph";
	}

	Graph<ContainerNode, Edge>* loadG = Graph<ContainerNode, Edge>::loadGraph(
			"X:\\codigo\\EvoCoder_Release_v1\\EvoCoder\\test_container.graph");

	if ((loadG != NULL)) {
		LOG(DEBUG)<< "Grafo cargado..." << endl;
		LOG(DEBUG) << loadG->toString() << endl;

		loadG->removeNode(0);
		LOG(DEBUG) << "Grafo: borrar nodo 0..." << endl;
		LOG(DEBUG) << loadG->toString() << endl;

		Edge tempE(1, 2);
		loadG->removeEdge(tempE);
		LOG(DEBUG) << "Grafo: borrar arista 1->2..." << endl;
		LOG(DEBUG) << loadG->toString() << endl;

	} else {
		LOG(ERROR) << "error loading graph";
	}

	delete loadG;
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
		LOG(DEBUG)<< *it << endl;
	}
}

void Test::testVariableTable(boost::shared_ptr<VariableTable> t,
		const std::string & name) {
	t->setValue("tiempo", 0.0);
	LOG(DEBUG)<< "valor para tiempo(0.0) = " << patch::to_string(t->getVaue("tiempo"));
	t->setValue("tiempo", 1.0);
	LOG(DEBUG)<< "valor para tiempo(1.0) = " << patch::to_string(t->getVaue("tiempo"));

	try {
		t->getVaue(name);
	} catch (invalid_argument & e) {
		LOG(DEBUG)<< "excepcion invalid_argument = " << e.what();
	}
}

void Test::testMathematicVariable() {
	LOG(INFO)<< "TEST MATHEMATIC VARIABLE...";
	boost::shared_ptr<VariableTable> t(new VariableTable());

	boost::shared_ptr<MathematicOperable> ve(new VariableEntry("test", t));
	boost::shared_ptr<MathematicOperable> ve2(new VariableEntry("test2", t));

	t->setValue("test",3.0);
	t->setValue("test2",2.0);

	boost::shared_ptr<MathematicOperable> cn(new ConstantNumber(7.0));
	boost::shared_ptr<MathematicOperable> ao(new ArithmeticOperation(ve, arithmetic::minus, cn));
	boost::shared_ptr<MathematicOperable> ao2(new ArithmeticOperation(ve2, arithmetic::multiply, ao));
	boost::shared_ptr<MathematicOperable> ao22(new ArithmeticOperation(ve2, arithmetic::multiply, ao));

	LOG(INFO) << "test(3) - 7 = -4 : " << patch::to_string(ao.get()->getValue());
	LOG(INFO) << "test2(2) * (test(3) - 7) = -8 : " << patch::to_string(ao2.get()->getValue());

	LOG(INFO) << "ao2 == ao22 ? TRUE : " << ao22.get()->equal(ao2.get());
	LOG(INFO) << "ao2 == ve2 ? FALSE : " << ao22.get()->equal(ve2.get());

	t->setValue("test", 5.0);
	LOG(INFO) << "test(5) - 7 = -2 : " << patch::to_string(ao.get()->getValue());

	boost::shared_ptr<MathematicOperable> ao222 = ao22;
	LOG(INFO) << "ao22 == ao22 : " << ao22.get()->equal(ao222.get());

}

void Test::testComparisonVariable() {
	LOG(INFO)<< "TEST COMPARISON VARIABLE...";
	boost::shared_ptr<VariableTable> t(new VariableTable());
	t->setValue("test", 3);
	t->setValue("test2", 2);

	boost::shared_ptr<MathematicOperable> ve(new VariableEntry("test", t));
	boost::shared_ptr<MathematicOperable> ve2(new VariableEntry("test2", t));
	boost::shared_ptr<MathematicOperable> cn7(new ConstantNumber(7.0));
	boost::shared_ptr<MathematicOperable> cn1(new ConstantNumber(1.0));
	boost::shared_ptr<MathematicOperable> ao(new ArithmeticOperation(ve, arithmetic::minus, cn7));

	//test

	boost::shared_ptr<ComparisonOperable> sc1(new SimpleComparison(false,ve,comparison::greater_equal,cn7));
	boost::shared_ptr<ComparisonOperable> sc2(new SimpleComparison(false,ve,comparison::less,ve2));

	boost::shared_ptr<ComparisonOperable> sc3(new SimpleComparison(true,ve,comparison::greater_equal,cn7));
	boost::shared_ptr<ComparisonOperable> sc4(new SimpleComparison(false,ve,comparison::greater_equal,cn1));
	boost::shared_ptr<ComparisonOperable> bc(new BooleanComparison(false, sc4, logical::conjunction, sc3));

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

ProtocolGraph* Test::MakeTurbidostat(boost::shared_ptr<VariableTable> table,
		boost::shared_ptr<Mapping> map) {

	AutoEnumerate serial;
	ProtocolGraph* protocol = new ProtocolGraph("turbidostat");

	boost::shared_ptr<VariableEntry> epsilon(
			new VariableEntry("epsilon", table));
	boost::shared_ptr<VariableEntry> threshold(
			new VariableEntry("threshold", table));
	boost::shared_ptr<VariableEntry> rate(new VariableEntry("rate", table));

	boost::shared_ptr<MathematicOperable> mepsilon(
			new VariableEntry("epsilon", table));
	boost::shared_ptr<MathematicOperable> mthreshold(
			new VariableEntry("threshold", table));
	boost::shared_ptr<MathematicOperable> mrate(
			new VariableEntry("rate", table));

	boost::shared_ptr<MathematicOperable> num0_1(new ConstantNumber(0.1));
	boost::shared_ptr<MathematicOperable> num600(new ConstantNumber(600));
	boost::shared_ptr<MathematicOperable> num2(new ConstantNumber(2));

	OperationNode* op1 = new AssignationOperation(serial.getNextValue(),
			epsilon, num0_1); //epsilon = 1
	protocol->setStartNode(op1->getContainerId());

	OperationNode* op2 = new AssignationOperation(serial.getNextValue(),
			threshold, num600); //threshold = 600
	OperationNode* op3 = new AssignationOperation(serial.getNextValue(), rate,
			num2); //rate = 2

	protocol->addOperation(op1);
	protocol->addOperation(op2);
	protocol->addOperation(op3);

	boost::shared_ptr<ComparisonOperable> tautology(new Tautology());
	protocol->connectOperation(op1, op2, tautology);
	protocol->connectOperation(op2, op3, tautology);

	boost::shared_ptr<MathematicOperable> num1000(new ConstantNumber(1000));
	OperationNode* op4 = new LoadContainerOperation(serial.getNextValue(), map,
			1, num1000); //loadContainer(1, 1000ml)
	OperationNode* op5 = new LoadContainerOperation(serial.getNextValue(), map,
			2, num1000); //loadContainer(2, 1000ml)
	OperationNode* op6 = new LoadContainerOperation(serial.getNextValue(), map,
			3, num1000); //loadContainer(3, 1000ml)

	protocol->addOperation(op4);
	protocol->addOperation(op5);
	protocol->addOperation(op6);

	protocol->connectOperation(op3, op4, tautology);
	protocol->connectOperation(op4, op5, tautology);
	protocol->connectOperation(op5, op6, tautology);

	boost::shared_ptr<MathematicOperable> num20(new ConstantNumber(20));
	boost::shared_ptr<VariableEntry> time(
			new VariableEntry(TIME_VARIABLE, table));
	boost::shared_ptr<MathematicOperable> mtime(
			new VariableEntry(TIME_VARIABLE, table));

	boost::shared_ptr<ComparisonOperable> comp1(
			new SimpleComparison(false, mtime, comparison::less, num20));

	OperationNode* loop1 = new LoopNode(serial.getNextValue(), comp1,
			boost::shared_ptr<ComparisonOperable>(new Tautology())); //while (t < 20)

	protocol->addOperation(loop1);
	protocol->connectOperation(op6, loop1, comp1);

	boost::shared_ptr<VariableEntry> od(new VariableEntry("od", table));
	boost::shared_ptr<MathematicOperable> mod(new VariableEntry("od", table));
	OperationNode* op7 = new MeasureOD(serial.getNextValue(), map, 2, od); //od = measureOd(2)

	protocol->addOperation(op7);
	protocol->connectOperation(loop1, op7, comp1);

	boost::shared_ptr<MathematicOperable> num1(new ConstantNumber(1.0));
	boost::shared_ptr<VariableEntry> normOD(new VariableEntry("normOD", table));
	boost::shared_ptr<MathematicOperable> mnormOD(
			new VariableEntry("normOD", table));

	boost::shared_ptr<MathematicOperable> operation1_1( //(od - threshold)
			new ArithmeticOperation(mod, arithmetic::minus, mthreshold));
	boost::shared_ptr<MathematicOperable> operation1_2( //(od - threshold) /threshold
			new ArithmeticOperation(operation1_1, arithmetic::divide,
					mthreshold));
	boost::shared_ptr<MathematicOperable> operation1( //1 + (od - threshold) /threshold
			new ArithmeticOperation(num1, arithmetic::plus, operation1_2));

	OperationNode* op8 = new AssignationOperation(serial.getNextValue(), normOD,
			operation1); // normOD = 1 + (od - threshold) /threshold

	protocol->addOperation(op8);
	protocol->connectOperation(op7, op8, tautology);

	boost::shared_ptr<ComparisonOperable> comp2in(
			new SimpleComparison(false, normOD, comparison::greater, num1));
	boost::shared_ptr<ComparisonOperable> comp2out(
			new SimpleComparison(true, normOD, comparison::greater, num1));
	DivergeNode* if1 = new DivergeNode(serial.getNextValue(), comp2in,
			comp2out); //if (normOD > 1)

	protocol->addOperation(if1);
	protocol->connectOperation(op8, if1, tautology);

	boost::shared_ptr<ComparisonOperable> comp3in(
			new SimpleComparison(false, normOD, comparison::less, num1));
	boost::shared_ptr<ComparisonOperable> comp3out(
			new SimpleComparison(true, normOD, comparison::less, num1));
	DivergeNode* if2 = new DivergeNode(serial.getNextValue(), comp3in,
			comp3out); //if (normOD < 1)

	boost::shared_ptr<MathematicOperable> operation2_1( //(normOD - 1)
			new ArithmeticOperation(mnormOD, arithmetic::minus, num1));
	boost::shared_ptr<MathematicOperable> operation2( // 1 + (normOD - 1)
			new ArithmeticOperation(num1, arithmetic::plus, operation2_1));

	boost::shared_ptr<VariableEntry> prop(new VariableEntry("prop", table));
	boost::shared_ptr<MathematicOperable> mprop(
			new VariableEntry("prop", table));
	OperationNode* op9 = new AssignationOperation(serial.getNextValue(), prop,
			operation2); // prop = 1 + (normOD - 1)

	protocol->addOperation(if2);
	protocol->addOperation(op9);

	protocol->connectOperation(if1, op9, comp2in);
	protocol->connectOperation(if1, if2, comp2out);

	boost::shared_ptr<MathematicOperable> operation3_1( //(normOD - 1)
			new ArithmeticOperation(mnormOD, arithmetic::minus, num1));
	boost::shared_ptr<MathematicOperable> operation3( // 1 - (normOD - 1)
			new ArithmeticOperation(num1, arithmetic::minus, operation2_1));

	OperationNode* op10 = new AssignationOperation(serial.getNextValue(), prop,
			operation3); // prop = 1 - (normOD - 1)

	OperationNode* op11 = new AssignationOperation(serial.getNextValue(), prop,
			num1); //prop = 1

	protocol->addOperation(op10);
	protocol->addOperation(op11);

	protocol->connectOperation(if2, op10, comp3in);
	protocol->connectOperation(if2, op11, comp3out);

	boost::shared_ptr<MathematicOperable> operation4_1(
			new ArithmeticOperation(mprop, arithmetic::minus, num1)); // prop -1
	boost::shared_ptr<MathematicOperable> operation4_2(
			new UnaryOperation(operation4_1, unaryOperations::absoluteValue)); // fabs(prop -1)
	boost::shared_ptr<MathematicOperable> operation4(
			new ArithmeticOperation(operation4_2, arithmetic::minus, num1)); // fabs(prop -1) -1

	boost::shared_ptr<ComparisonOperable> comp4in(
			new SimpleComparison(false, operation4, comparison::greater,
					epsilon)); // fabs(prop -1) -1 > epsilon
	boost::shared_ptr<ComparisonOperable> comp4out(
			new SimpleComparison(true, operation4, comparison::greater,
					epsilon)); // !(fabs(prop -1) -1 > epsilon)

	DivergeNode* if3 = new DivergeNode(serial.getNextValue(), comp4in,
			comp4out); //if (fabs(prop -1) -1 > epsilon)
	if2->setEndNode(if3);
	if1->setEndNode(if3);

	protocol->addOperation(if3);

	protocol->connectOperation(op9, if3, tautology);
	protocol->connectOperation(op10, if3, tautology);
	protocol->connectOperation(op11, if3, tautology);

	boost::shared_ptr<MathematicOperable> operation5(
			new ArithmeticOperation(prop, arithmetic::multiply, rate)); // prop * rate
	OperationNode* op12 = new AssignationOperation(serial.getNextValue(), rate,
			operation5); // rate = prop * rate

	protocol->addOperation(op12);
	protocol->connectOperation(if3, op12, comp4in);

	OperationNode* op13 = new SetContinousFlow(serial.getNextValue(), map, 1, 2,
			rate); // setcontinousFlow(1,2,rate)

	protocol->addOperation(op13);
	protocol->connectOperation(op12, op13, tautology);

	OperationNode* op14 = new SetContinousFlow(serial.getNextValue(), map, 2, 3,
			rate); // setcontinousFlow(2,3,rate)

	protocol->addOperation(op14);
	protocol->connectOperation(op13, op14, tautology);

	OperationNode* timeStep = new TimeStep(serial.getNextValue(), map, time);

	if3->setEndNode(timeStep);

	protocol->addOperation(timeStep);

	protocol->connectOperation(op14, timeStep, tautology);
	protocol->connectOperation(if3, timeStep, comp4out);
	protocol->connectOperation(timeStep, loop1, tautology);

	return protocol;
}

void Test::testUnaryOperation() {
	boost::shared_ptr<ConstantNumber> cn(new ConstantNumber(3.3));
	UnaryOperation op(cn, unaryOperations::absoluteValue);
	LOG(INFO)<< "abs(3.3):" << patch::to_string(op.getValue());
}

void Test::testSketcher() {
	boost::shared_ptr<VariableTable> t(new VariableTable());
	ExecutableMachineGraph* machine = new ExecutableMachineGraph("testMachine");
	boost::shared_ptr<Mapping> map(new Mapping(machine, "testMamchine"));

	ProtocolGraph* protocol = makeSimpleProtocol(t, map);

	LOG(INFO)<< "printing protocol...";
	protocol->printProtocol("protocol.graph");

	EvoCoder* evo = new EvoCoder(protocol, t, map.get());

	LOG(INFO)<< "Sketching... " << evo->sketcher();
	LOG(INFO)<< "printing sketch...";
	map.get()->printSketch("turbidostatMachine.graph");

	delete protocol;
	delete machine;
	delete evo;
}

void Test::testMapping() {
	boost::shared_ptr<VariableTable> t(new VariableTable());
	ProtocolGraph* protocol = new ProtocolGraph("testProtocol");
	ExecutableMachineGraph* machine = new ExecutableMachineGraph("testMachine");
	Mapping* map = new Mapping(machine, "test");

	EvoCoder* evo = new EvoCoder(protocol, t, map);

	map->setSketching();

	//test: actuador antes de declarar nodo
	map->setContinuosFlow(1, 2, 0.0);
	map->setContinuosFlow(2, 3, 0.0);
	map->measureOD(2);
	map->stir(2, 0.0);

	LOG(INFO)<< "Sketching... " << evo->sketcher();
	map->printSketch("mappingTest.graph");

	delete machine;
	delete evo;
	delete map;
	delete protocol;
}

void Test::testFlow() {
	std::priority_queue<Flow<Edge>*, vector<Flow<Edge>*>,
			FlowPtrComparator<Edge>> heap;

	Flow<Edge>* f1 = new Flow<Edge>(1, 3);
	Edge* edge13 = new Edge(1, 3);
	f1->append(edge13);

	heap.push(f1);

	Flow<Edge>* f2 = new Flow<Edge>(1, 3);
	Edge* edge12 = new Edge(1, 2);
	f2->append(edge12);
	f2->append(edge13);

	heap.push(f2);

	while (!heap.empty()) {
		Flow<Edge>* actual = heap.top();
		heap.pop();
		LOG(INFO)<< actual->toText();
	}

}
void Test::testSerialPort_send() {
	try {
		SerialSender* s = new SerialSender("\\\\.\\COM3");

		for (int i = 0; i < 10; i++) {
			LOG(INFO)<< "sending " << i << "...";
			LOG(INFO)<< "correct: " << s->sendString(patch::to_string(i));
			Sleep(2000);
		}

	} catch (std::ios_base::failure& e) {
		LOG(INFO) << "error: " << e.what();
	}
}

ProtocolGraph* Test::makeSimpleProtocol(boost::shared_ptr<VariableTable> table,
		boost::shared_ptr<Mapping> map) {

	AutoEnumerate serial;
	ProtocolGraph* protocol = new ProtocolGraph("simpleProtocol");

	boost::shared_ptr<ComparisonOperable> tautology(new Tautology());

	boost::shared_ptr<VariableEntry> epsilon(
			new VariableEntry("epsilon", table));
	boost::shared_ptr<MathematicOperable> mepsilon(
			new VariableEntry("epsilon", table));
	boost::shared_ptr<MathematicOperable> num0_5(new ConstantNumber(0.5));
	boost::shared_ptr<MathematicOperable> num10(new ConstantNumber(10));

	OperationNode* op1 = new AssignationOperation(serial.getNextValue(),
			epsilon, num0_5); //epsilon = 0.5

	boost::shared_ptr<MathematicOperable> num1000(new ConstantNumber(1000));
	OperationNode* op4 = new LoadContainerOperation(serial.getNextValue(), map,
			1, num1000); //loadContainer(1, 1000ml)
	OperationNode* op5 = new LoadContainerOperation(serial.getNextValue(), map,
			2, num1000); //loadContainer(2, 1000ml)
	OperationNode* op6 = new LoadContainerOperation(serial.getNextValue(), map,
			3, num1000); //loadContainer(3, 1000ml)

	protocol->addOperation(op1);
	protocol->addOperation(op4);
	protocol->addOperation(op5);
	protocol->addOperation(op6);

	protocol->connectOperation(op1, op4, tautology);
	protocol->connectOperation(op4, op5, tautology);
	protocol->connectOperation(op5, op6, tautology);

	boost::shared_ptr<ComparisonOperable> contradiction(new Tautology());
	OperationNode* loop1 = new LoopNode(serial.getNextValue(), tautology,
			contradiction); //while (true)

	protocol->addOperation(loop1);
	protocol->connectOperation(op6, loop1, tautology);

	boost::shared_ptr<VariableEntry> od(new VariableEntry("od", table));
	boost::shared_ptr<MathematicOperable> mod(new VariableEntry("od", table));
	OperationNode* op7 = new MeasureOD(serial.getNextValue(), map, 3, od); //od = measureOd(2)

	protocol->addOperation(op7);
	protocol->connectOperation(loop1, op7, tautology);

	boost::shared_ptr<ComparisonOperable> comp2in(
			new SimpleComparison(false, mod, comparison::greater, mepsilon));
	boost::shared_ptr<ComparisonOperable> comp2out(
			new SimpleComparison(true, mod, comparison::greater, mepsilon));
	DivergeNode* if1 = new DivergeNode(serial.getNextValue(), comp2in,
			comp2out); //if (od > 0.5)

	protocol->addOperation(if1);
	protocol->connectOperation(op7, if1, tautology);

	OperationNode* op8 = new Transfer(serial.getNextValue(), map, 1, 3, num10);
	OperationNode* op9 = new Transfer(serial.getNextValue(), map, 3, 4, num10);

	protocol->addOperation(op8);
	protocol->connectOperation(if1, op8, comp2in);
	protocol->addOperation(op9);
	protocol->connectOperation(op8, op9, tautology);
	protocol->connectOperation(op9, loop1, tautology);

	OperationNode* op10 = new Transfer(serial.getNextValue(), map, 2, 3, num10);
	OperationNode* op11 = new Transfer(serial.getNextValue(), map, 3, 4, num10);

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

		LOG(INFO)<< "recibiendo datos...";
		for (int i = 0; i < 10; i++) {
			LOG(INFO)<< i << ":" << s->receiveString();
			Sleep(1500);
		}

	} catch (std::ios_base::failure& e) {
		LOG(INFO) << "error: " << e.what();
	}
}

void Test::testExecutableMachineGraph() {
	CommandSender* communications = new SerialSender("\\\\.\\COM3");
	LOG(INFO) << "creating machine...";
	ExecutableMachineGraph* machine = makeSimpleMachine(communications);

	ContainerNodeType cinlet(MovementType::continuous, ContainerType::inlet);
	ContainerNodeType sink(MovementType::irrelevant, ContainerType::sink);

	LOG(INFO) << "printing graph...";
	machine->saveGraph("exMachine.graph");

	LOG(INFO) << "not available 2";
	machine->addUsedNode(4);

	LOG(INFO) << "getting flows inlet to sink...";
	std::priority_queue<Flow<Edge>*, vector<Flow<Edge>*>,
				FlowPtrComparator<Edge>>* f = machine->getAvailableFlows(cinlet, sink);

	int i = 0;
	while(!f->empty()) {
		LOG(INFO) << "Flow: " << i << " " << f->top()->toText();
		f->pop();
		i++;
	}

	LOG(INFO) << "destroying machine";
	delete machine;
	delete communications;
}

ExecutableMachineGraph* Test::makeSimpleMachine(CommandSender* communications) {
	ExecutableMachineGraph* machine = new ExecutableMachineGraph(
			"simpleMachine");

	boost::shared_ptr<Control> control(new EvoprogSixwayValve(communications,7));
	boost::shared_ptr<Light> light(new EvoprogLight(communications, 2, 3));
	boost::shared_ptr<Temperature> temperature(
			new EvoprogTemperature(communications, 1));
	boost::shared_ptr<Extractor> cExtractor(
			new EvoprogContinuousPump(communications, 13));
	boost::shared_ptr<Extractor> dExtractor(
			new EvoprogDiscretePump(communications, 14));
	boost::shared_ptr<Injector> dummyInjector(
			new EvoprogDummyInjector(communications));
	boost::shared_ptr<Mixer> mix(new EvoprogMixer(communications, 4));

	ExecutableContainerNode* cInlet1 = new InletContainer(1,100.0,cExtractor);
	cInlet1->setLight(light);
	ExecutableContainerNode* dInlet2 = new InletContainer(2,100.0,dExtractor);
	dInlet2->setTemperature(temperature);
	ExecutableContainerNode* cSwtInlet3 = new ConvergentSwitchInlet(3,100.0,dummyInjector,cExtractor,control);
	cSwtInlet3->setMix(mix);
	ExecutableContainerNode* sink = new SinkContainer(4,100.0,dummyInjector);

	machine->addContainer(cInlet1);
	machine->addContainer(dInlet2);
	machine->addContainer(cSwtInlet3);
	machine->addContainer(sink);

	machine->connectExecutableContainer(1,3);
	machine->connectExecutableContainer(2,3);
	machine->connectExecutableContainer(3,4);

	return machine;
}

void Test::testEvoprogComponents() {
	try {
		CommandSender* com = new SerialSender("\\\\.\\COM3");
		Extractor* ext = new EvoprogContinuousPump(com, 2);
		ODSensor* od = new EvoprogOdSensor(com, 3);
		Light* light = new EvoprogLight(com, 4, 5);

		LOG(INFO)<< "extracting liquid";
		ext->extractLiquid(1.0);

		LOG(INFO)<< "reading sensor";
		LOG(INFO)<< "read " << od->readOd();

		LOG(INFO)<< "send light command...";
		light->applyLight(20.0, 50.0);

	} catch (std::ios_base::failure& e) {
		LOG(INFO)<< "error: " << e.what();
	} catch (std::invalid_argument& e) {
		LOG(INFO) << "error: " << e.what();
	}
}
