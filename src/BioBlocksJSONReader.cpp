#include "BioBlocksJSONReader.h"

BioBlocksJSONReader* BioBlocksJSONReader::m_pInstance = NULL;

using json = nlohmann::json;

void BioBlocksJSONReader::freeCommandInterface()
{
	if (m_pInstance) {
		delete m_pInstance;
	}
}


BioBlocksJSONReader::BioBlocksJSONReader()
{
}

double BioBlocksJSONReader::parseVolume(const std::string & text)
{
	float value = 0;

	boost::char_separator<char> sep{ ":" };
	boost::tokenizer<boost::char_separator<char>> tok{ text, sep };
	boost::tokenizer< boost::char_separator<char> >::iterator beg = tok.begin();
	beg++;

	string chunk = *beg;

	return patch::stod(value, chunk.c_str());
}


BioBlocksJSONReader::~BioBlocksJSONReader()
{
}

ProtocolGraph* BioBlocksJSONReader::loadFile(const std::string & path)
{
	ProtocolGraph* protocol = new ProtocolGraph("bioBlocks_graph");
	std::shared_ptr<ComparisonOperable> tautology = std::make_shared<Tautology>();
	std::ifstream in(path);
	json js;

	try {
		std::shared_ptr<OperationNode> lastOp;

		in >> js;
		
		json jrefs = js["refs"];

		for (json::iterator it = jrefs.begin(); it != jrefs.end(); ++it) {
			std::string name = (*it)["id"];
			std::string volume_str = (*it)["volume"];
			float volume;
			patch::stod(volume, volume_str.c_str());

			auto entry = containerMap.find(name);
			if (entry == containerMap.end()) {
				int containerID = table_sequence.getNextValue();
				containerMap.insert(std::make_pair(name, containerID));
				
				std::shared_ptr<MathematicOperable> volumeObject = std::make_shared<ConstantNumber>(volume);
				std::shared_ptr<OperationNode> actual_op = std::make_shared<LoadContainerOperation>(graph_sequence.getNextValue(), containerID, volumeObject);
				protocol->addOperation(actual_op);

				if (lastOp) {
					protocol->connectOperation(lastOp, actual_op, tautology);
				}
				else {
					protocol->setStartNode(0);
				}

				lastOp = actual_op;
			} else {
				LOG(ERROR) << "two containers has the same name: " + (*it)["id"];
			}
		}

		jrefs = js["instructions"];

		for (json::iterator it = jrefs.begin(); it != jrefs.end(); ++it) {
			json op = (*it)["groups"][0];
			json value = op.begin().value();
			string key = op.begin().key();

			json to = value["to"];
			json from = value["from"];

			std::shared_ptr<OperationNode> actual_op;
			if (to.is_array()) { //one to many
				
				for (json::iterator itto = to.begin(); itto != to.end(); ++itto) {
					string targetName = (*itto)["well"].get<string>();
					int containerTarget = containerMap.at(targetName);
					
					if (key.compare("continuous transfer") == 0) {
						int containerSource = containerMap.at(from["well"].get<string>());
						double volume = from["flow rate"].get<double>();
						std::shared_ptr<MathematicOperable> volumeObject = std::make_shared<ConstantNumber>(volume);

						actual_op = std::make_shared<SetContinousFlow>(graph_sequence.getNextValue(), containerSource, containerTarget, volumeObject);
					}
					else {
						int containerSource = containerMap.at(from.get<string>());
						double volume = parseVolume((*itto)["volume"]);
						std::shared_ptr<MathematicOperable> volumeObject = std::make_shared<ConstantNumber>(volume);

						actual_op = std::make_shared<Transfer>(graph_sequence.getNextValue(), containerSource, containerTarget, volumeObject);
					}

					if (lastOp) {
						protocol->connectOperation(lastOp, actual_op, tautology);
					}
					else {
						protocol->setStartNode(0);
					}
					lastOp = actual_op;
				}
			}
			else if (from.is_array()) { //many to one
				int containerTarget = containerMap.at(to.get<string>());
				for (json::iterator itfrom = to.begin(); itfrom != to.end(); ++itfrom) {
					int containerSource = containerMap.at((*itfrom)["well"].get<string>());

					if (key.compare("continuous transfer") == 0) {
						double volume = value["flow rate"].get<double>();
						std::shared_ptr<MathematicOperable> volumeObject = std::make_shared<ConstantNumber>(volume);
						actual_op = std::make_shared<SetContinousFlow>(graph_sequence.getNextValue(), containerSource, containerTarget, volumeObject);
					}
					else {
						double volume = parseVolume((*itfrom)["volume"]);
						std::shared_ptr<MathematicOperable> volumeObject = std::make_shared<ConstantNumber>(volume);
						actual_op = std::make_shared<Transfer>(graph_sequence.getNextValue(), containerSource, containerTarget, volumeObject);
					}

					if (lastOp) {
						protocol->connectOperation(lastOp, actual_op, tautology);
					}
					else {
						protocol->setStartNode(0);
					}
					lastOp = actual_op;
				}
			}
			else { // one to one
				double volume = parseVolume(value["volume"]);
				int containerSource = containerMap.at(from.get<string>());
				int containerTarget = containerMap.at(to.get<string>());
				std::shared_ptr<MathematicOperable> volumeObject = std::make_shared<ConstantNumber>(volume);
				
				if (key.compare("continuous transfer") == 0) {
					actual_op = std::make_shared<SetContinousFlow>(graph_sequence.getNextValue(), containerSource, containerTarget, volumeObject);
				}
				else {
					actual_op = std::make_shared<Transfer>(graph_sequence.getNextValue(), containerSource, containerTarget, volumeObject);
				}
			}

			if (lastOp) {
				protocol->connectOperation(lastOp, actual_op, tautology);
			}
			else {
				protocol->setStartNode(0);
			}

			lastOp = actual_op;
		}

	}
	catch (std::exception & e) {
		LOG(ERROR) << e.what();
	}

	return protocol;
	//return NULL;
}
