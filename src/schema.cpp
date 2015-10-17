#include "schema.h"

namespace SAPHRON
{
	//INSERT_DEF_HERE
	std::string SAPHRON::JsonSchema::Simulation = "{\"properties\": {\"sweeps\": {\"type\": \"integer\", \"minimum\": 1}, \"units\": {\"type\": \"string\", \"enum\": [\"real\", \"reduced\"]}, \"seed\": {\"type\": \"integer\", \"minimum\": 0}, \"simtype\": {\"type\": \"string\", \"enum\": [\"standard\", \"DOS\"]}, \"mps\": {\"type\": \"integer\", \"minimum\": 1}}, \"required\": [\"simtype\", \"sweeps\"], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::ForceFields = "{\"properties\": {\"electrostatic\": {\"type\": \"array\"}, \"bonded\": {\"type\": \"array\"}, \"nonbonded\": {\"type\": \"array\"}}, \"additionalProperties\": false, \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::LebwholLasher = "{\"properties\": {\"species\": {\"items\": {\"type\": \"string\"}, \"maxItems\": 2, \"minItems\": 2, \"type\": \"array\", \"additionalItems\": false}, \"epsilon\": {\"type\": \"number\"}, \"type\": {\"type\": \"string\", \"enum\": [\"LebwohlLasher\"]}, \"gamma\": {\"type\": \"number\"}}, \"additionalProperties\": false, \"required\": [\"type\", \"epsilon\", \"gamma\", \"species\"], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::LennardJones = "{\"properties\": {\"species\": {\"items\": {\"type\": \"string\"}, \"maxItems\": 2, \"minItems\": 2, \"type\": \"array\", \"additionalItems\": false}, \"sigma\": {\"exclusiveMinimum\": true, \"type\": \"number\", \"minimum\": 0}, \"type\": {\"type\": \"string\", \"enum\": [\"LennardJones\"]}, \"epsilon\": {\"type\": \"number\", \"minimum\": 0}}, \"additionalProperties\": false, \"required\": [\"type\", \"sigma\", \"epsilon\", \"species\"], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::Worlds = "{\"minItems\": 1, \"items\": {\"properties\": {\"components\": {\"type\": \"object\"}, \"dimensions\": {\"items\": {\"type\": \"number\", \"minimum\": 0}, \"maxItems\": 3, \"minItems\": 3, \"type\": \"array\", \"additionalItems\": false}, \"particles\": {\"type\": \"array\"}, \"type\": {\"type\": \"string\", \"enum\": [\"Simple\"]}, \"nlist_cutoff\": {\"exclusiveMinimum\": true, \"type\": \"number\", \"minimum\": 0}, \"temperature\": {\"type\": \"number\", \"minimum\": 0}, \"r_cutoff\": {\"exclusiveMinimum\": true, \"type\": \"number\", \"minimum\": 0}, \"seed\": {\"type\": \"integer\", \"minimum\": 0}}, \"required\": [\"type\", \"dimensions\", \"r_cutoff\", \"components\"], \"type\": \"object\"}, \"type\": \"array\"}";
	std::string SAPHRON::JsonSchema::SimpleWorld = "{\"properties\": {\"components\": {\"type\": \"object\"}, \"dimensions\": {\"items\": {\"type\": \"number\", \"minimum\": 0}, \"maxItems\": 3, \"minItems\": 3, \"type\": \"array\", \"additionalItems\": false}, \"particles\": {\"type\": \"array\"}, \"type\": {\"type\": \"string\", \"enum\": [\"Simple\"]}, \"nlist_cutoff\": {\"exclusiveMinimum\": true, \"type\": \"number\", \"minimum\": 0}, \"temperature\": {\"type\": \"number\", \"minimum\": 0}, \"r_cutoff\": {\"exclusiveMinimum\": true, \"type\": \"number\", \"minimum\": 0}, \"seed\": {\"type\": \"integer\", \"minimum\": 0}}, \"required\": [\"type\", \"dimensions\", \"r_cutoff\", \"components\"], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::Particles = "{\"minItems\": 1, \"items\": {\"minItems\": 4, \"items\": [{\"type\": \"integer\", \"minimum\": 1}, {\"type\": \"string\"}, {\"type\": \"string\"}, {\"items\": {\"type\": \"number\", \"minimum\": 0}, \"maxItems\": 3, \"minItems\": 3, \"type\": \"array\", \"additionalItems\": false}, {\"items\": {\"type\": \"number\"}, \"maxItems\": 3, \"minItems\": 3, \"type\": \"array\", \"additionalItems\": false}, {\"type\": \"string\"}], \"type\": \"array\", \"additionalItems\": false}, \"type\": \"array\", \"additionalItems\": false}";
	std::string SAPHRON::JsonSchema::Site = "{\"minItems\": 4, \"items\": [{\"type\": \"integer\", \"minimum\": 1}, {\"type\": \"string\"}, {\"type\": \"string\"}, {\"items\": {\"type\": \"number\", \"minimum\": 0}, \"maxItems\": 3, \"minItems\": 3, \"type\": \"array\", \"additionalItems\": false}, {\"items\": {\"type\": \"number\"}, \"maxItems\": 3, \"minItems\": 3, \"type\": \"array\", \"additionalItems\": false}, {\"type\": \"string\"}], \"type\": \"array\", \"additionalItems\": false}";
	std::string SAPHRON::JsonSchema::Components = "{\"patternProperties\": {\"^[A-z][A-z0-9]+$\": {\"properties\": {\"mass\": {\"type\": \"number\", \"minimum\": 0}, \"count\": {\"type\": \"integer\", \"minimum\": 1}, \"charge\": {\"type\": \"number\"}, \"children\": {\"minItems\": 1, \"items\": {\"properties\": {\"mass\": {\"type\": \"number\", \"minimum\": 0}, \"species\": {\"type\": \"string\"}, \"charge\": {\"type\": \"number\"}}, \"required\": [\"species\"], \"type\": \"object\"}, \"type\": \"array\"}}, \"additionalProperties\": false, \"required\": [\"count\"], \"type\": \"object\", \"minProperties\": 1}}, \"minProperties\": 1, \"type\": \"object\", \"additionalProperties\": false}";
	std::string SAPHRON::JsonSchema::Selector = "{}";
	std::string SAPHRON::JsonSchema::Director = "{\"items\": {\"type\": \"number\"}, \"maxItems\": 3, \"minItems\": 3, \"type\": \"array\", \"additionalItems\": false}";
	std::string SAPHRON::JsonSchema::Observer = "{\"properties\": {\"flags\": {\"properties\": {\"world_count\": {\"maximum\": 1, \"type\": \"integer\", \"minimum\": 0}, \"world_composition\": {\"maximum\": 1, \"type\": \"integer\", \"minimum\": 0}, \"identifier\": {\"maximum\": 1, \"type\": \"integer\", \"minimum\": 0}, \"world_density\": {\"maximum\": 1, \"type\": \"integer\", \"minimum\": 0}, \"temperature\": {\"maximum\": 1, \"type\": \"integer\", \"minimum\": 0}, \"acceptance\": {\"maximum\": 1, \"type\": \"integer\", \"minimum\": 0}, \"sweeps\": {\"maximum\": 1, \"type\": \"integer\", \"minimum\": 0}, \"pressure\": {\"maximum\": 1, \"type\": \"integer\", \"minimum\": 0}, \"world_volume\": {\"maximum\": 1, \"type\": \"integer\", \"minimum\": 0}, \"energy\": {\"maximum\": 1, \"type\": \"integer\", \"minimum\": 0}}, \"type\": \"object\"}, \"frequency\": {\"type\": \"integer\", \"minimum\": 1}}, \"oneOf\": [{\"properties\": {\"file_prefix\": {\"type\": \"string\"}}, \"required\": [\"file_prefix\"]}], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::CSVObserver = "{\"properties\": {\"file_prefix\": {\"type\": \"string\"}}, \"required\": [\"file_prefix\"]}";
	std::string SAPHRON::JsonSchema::TranslateMove = "{\"properties\": {\"dx\": {\"type\": \"number\", \"minimum\": 0}, \"type\": {\"type\": \"string\", \"enum\": [\"Translate\"]}, \"seed\": {\"type\": \"integer\", \"minimum\": 0}}, \"additionalProperties\": false, \"required\": [\"type\", \"dx\"], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::DirectorRotateMove = "{\"properties\": {\"type\": {\"type\": \"string\", \"enum\": [\"DirectorRotate\"]}, \"seed\": {\"type\": \"integer\", \"minimum\": 0}}, \"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::SpeciesSwapMove = "{\"properties\": {\"type\": {\"type\": \"string\", \"enum\": [\"SpeciesSwap\"]}}, \"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::ParticleSwapMove = "{\"properties\": {\"type\": {\"type\": \"string\", \"enum\": [\"ParticleSwap\"]}, \"seed\": {\"type\": \"integer\", \"minimum\": 0}}, \"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::Moves = "{\"type\": \"array\"}";
	std::string SAPHRON::JsonSchema::RandomIdentityMove = "{\"properties\": {\"type\": {\"type\": \"string\", \"enum\": [\"IdentityChange\"]}}, \"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::FlipSpinMove = "{\"properties\": {\"type\": {\"type\": \"string\", \"enum\": [\"FlipSpin\"]}}, \"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::P2SAConnectivity = "{\"properties\": {\"selector\": {}, \"director\": {\"items\": {\"type\": \"number\"}, \"maxItems\": 3, \"minItems\": 3, \"type\": \"array\", \"additionalItems\": false}, \"coefficient\": {\"type\": \"number\"}, \"type\": {\"type\": \"string\", \"enum\": [\"P2SA\"]}}, \"additionalProperties\": false, \"required\": [\"type\", \"coefficient\", \"director\", \"selector\"], \"type\": \"object\"}";
	std::string SAPHRON::JsonSchema::Connectivities = "{\"items\": {\"oneOf\": [{\"properties\": {\"selector\": {}, \"director\": {\"items\": {\"type\": \"number\"}, \"maxItems\": 3, \"minItems\": 3, \"type\": \"array\", \"additionalItems\": false}, \"coefficient\": {\"type\": \"number\"}, \"type\": {\"type\": \"string\", \"enum\": [\"P2SA\"]}}, \"additionalProperties\": false, \"required\": [\"type\", \"coefficient\", \"director\", \"selector\"], \"type\": \"object\"}]}, \"type\": \"array\"}";
	
}