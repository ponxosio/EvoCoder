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


BioBlocksJSONReader::~BioBlocksJSONReader()
{
}

ProtocolGraph* BioBlocksJSONReader::loadFile(const std::string & path)
{
	/*ProtocolGraph* protocol = new ProtocolGraph("bioBlocks_graph");
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
				std::shared_ptr<OperationNode> actual_op = std::make_shared<LoadContainerOperation>(graph_sequence.getNextValue(), containerID, volume);
				protocol->addOperation(actual_op);

				if (lastOp) {
					protocol->connectOperation(lastOp, actual_op, tautology);
				}
				else {
					protocol->setStartNode(containerID);
				}

				lastOp = actual_op;
			} else {
				LOG(ERROR) << "two containers has the same name: " + (*it)["id"];
			}
		}
	}
	catch (std::exception & e) {
		LOG(ERROR) << e.what();
	}

	return protocol;*/
	return NULL;
}
