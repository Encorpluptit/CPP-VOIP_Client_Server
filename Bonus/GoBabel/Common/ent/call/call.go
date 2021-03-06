// Code generated by entc, DO NOT EDIT.

package call

const (
	// Label holds the string label denoting the call type in the database.
	Label = "call"
	// FieldID holds the string denoting the id field in the database.
	FieldID = "id"
	// FieldStartedAt holds the string denoting the started_at field in the database.
	FieldStartedAt = "started_at"
	// FieldFinishedAt holds the string denoting the finished_at field in the database.
	FieldFinishedAt = "finished_at"

	// EdgeConference holds the string denoting the conference edge name in mutations.
	EdgeConference = "conference"
	// EdgeParticipants holds the string denoting the participants edge name in mutations.
	EdgeParticipants = "participants"

	// Table holds the table name of the call in the database.
	Table = "calls"
	// ConferenceTable is the table the holds the conference relation/edge.
	ConferenceTable = "calls"
	// ConferenceInverseTable is the table name for the Conference entity.
	// It exists in this package in order to avoid circular dependency with the "conference" package.
	ConferenceInverseTable = "conferences"
	// ConferenceColumn is the table column denoting the conference relation/edge.
	ConferenceColumn = "conference_calls"
	// ParticipantsTable is the table the holds the participants relation/edge. The primary key declared below.
	ParticipantsTable = "user_calls"
	// ParticipantsInverseTable is the table name for the User entity.
	// It exists in this package in order to avoid circular dependency with the "user" package.
	ParticipantsInverseTable = "users"
)

// Columns holds all SQL columns for call fields.
var Columns = []string{
	FieldID,
	FieldStartedAt,
	FieldFinishedAt,
}

// ForeignKeys holds the SQL foreign-keys that are owned by the Call type.
var ForeignKeys = []string{
	"conference_calls",
}

var (
	// ParticipantsPrimaryKey and ParticipantsColumn2 are the table columns denoting the
	// primary key for the participants relation (M2M).
	ParticipantsPrimaryKey = []string{"user_id", "call_id"}
)
