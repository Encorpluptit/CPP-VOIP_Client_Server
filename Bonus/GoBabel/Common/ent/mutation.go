// Code generated by entc, DO NOT EDIT.

package ent

import (
	"GoBabel/Common/ent/call"
	"GoBabel/Common/ent/conference"
	"GoBabel/Common/ent/user"
	"context"
	"fmt"
	"sync"
	"time"

	"github.com/facebook/ent"
)

const (
	// Operation types.
	OpCreate    = ent.OpCreate
	OpDelete    = ent.OpDelete
	OpDeleteOne = ent.OpDeleteOne
	OpUpdate    = ent.OpUpdate
	OpUpdateOne = ent.OpUpdateOne

	// Node types.
	TypeCall       = "Call"
	TypeConference = "Conference"
	TypeUser       = "User"
)

// CallMutation represents an operation that mutate the Calls
// nodes in the graph.
type CallMutation struct {
	config
	op                Op
	typ               string
	id                *int
	started_at        *time.Time
	finished_at       *time.Time
	clearedFields     map[string]struct{}
	conference        map[int]struct{}
	removedconference map[int]struct{}
	done              bool
	oldValue          func(context.Context) (*Call, error)
}

var _ ent.Mutation = (*CallMutation)(nil)

// callOption allows to manage the mutation configuration using functional options.
type callOption func(*CallMutation)

// newCallMutation creates new mutation for $n.Name.
func newCallMutation(c config, op Op, opts ...callOption) *CallMutation {
	m := &CallMutation{
		config:        c,
		op:            op,
		typ:           TypeCall,
		clearedFields: make(map[string]struct{}),
	}
	for _, opt := range opts {
		opt(m)
	}
	return m
}

// withCallID sets the id field of the mutation.
func withCallID(id int) callOption {
	return func(m *CallMutation) {
		var (
			err   error
			once  sync.Once
			value *Call
		)
		m.oldValue = func(ctx context.Context) (*Call, error) {
			once.Do(func() {
				if m.done {
					err = fmt.Errorf("querying old values post mutation is not allowed")
				} else {
					value, err = m.Client().Call.Get(ctx, id)
				}
			})
			return value, err
		}
		m.id = &id
	}
}

// withCall sets the old Call of the mutation.
func withCall(node *Call) callOption {
	return func(m *CallMutation) {
		m.oldValue = func(context.Context) (*Call, error) {
			return node, nil
		}
		m.id = &node.ID
	}
}

// Client returns a new `ent.Client` from the mutation. If the mutation was
// executed in a transaction (ent.Tx), a transactional client is returned.
func (m CallMutation) Client() *Client {
	client := &Client{config: m.config}
	client.init()
	return client
}

// Tx returns an `ent.Tx` for mutations that were executed in transactions;
// it returns an error otherwise.
func (m CallMutation) Tx() (*Tx, error) {
	if _, ok := m.driver.(*txDriver); !ok {
		return nil, fmt.Errorf("ent: mutation is not running in a transaction")
	}
	tx := &Tx{config: m.config}
	tx.init()
	return tx, nil
}

// ID returns the id value in the mutation. Note that, the id
// is available only if it was provided to the builder.
func (m *CallMutation) ID() (id int, exists bool) {
	if m.id == nil {
		return
	}
	return *m.id, true
}

// SetStartedAt sets the started_at field.
func (m *CallMutation) SetStartedAt(t time.Time) {
	m.started_at = &t
}

// StartedAt returns the started_at value in the mutation.
func (m *CallMutation) StartedAt() (r time.Time, exists bool) {
	v := m.started_at
	if v == nil {
		return
	}
	return *v, true
}

// OldStartedAt returns the old started_at value of the Call.
// If the Call object wasn't provided to the builder, the object is fetched
// from the database.
// An error is returned if the mutation operation is not UpdateOne, or database query fails.
func (m *CallMutation) OldStartedAt(ctx context.Context) (v time.Time, err error) {
	if !m.op.Is(OpUpdateOne) {
		return v, fmt.Errorf("OldStartedAt is allowed only on UpdateOne operations")
	}
	if m.id == nil || m.oldValue == nil {
		return v, fmt.Errorf("OldStartedAt requires an ID field in the mutation")
	}
	oldValue, err := m.oldValue(ctx)
	if err != nil {
		return v, fmt.Errorf("querying old value for OldStartedAt: %w", err)
	}
	return oldValue.StartedAt, nil
}

// ResetStartedAt reset all changes of the "started_at" field.
func (m *CallMutation) ResetStartedAt() {
	m.started_at = nil
}

// SetFinishedAt sets the finished_at field.
func (m *CallMutation) SetFinishedAt(t time.Time) {
	m.finished_at = &t
}

// FinishedAt returns the finished_at value in the mutation.
func (m *CallMutation) FinishedAt() (r time.Time, exists bool) {
	v := m.finished_at
	if v == nil {
		return
	}
	return *v, true
}

// OldFinishedAt returns the old finished_at value of the Call.
// If the Call object wasn't provided to the builder, the object is fetched
// from the database.
// An error is returned if the mutation operation is not UpdateOne, or database query fails.
func (m *CallMutation) OldFinishedAt(ctx context.Context) (v time.Time, err error) {
	if !m.op.Is(OpUpdateOne) {
		return v, fmt.Errorf("OldFinishedAt is allowed only on UpdateOne operations")
	}
	if m.id == nil || m.oldValue == nil {
		return v, fmt.Errorf("OldFinishedAt requires an ID field in the mutation")
	}
	oldValue, err := m.oldValue(ctx)
	if err != nil {
		return v, fmt.Errorf("querying old value for OldFinishedAt: %w", err)
	}
	return oldValue.FinishedAt, nil
}

// ResetFinishedAt reset all changes of the "finished_at" field.
func (m *CallMutation) ResetFinishedAt() {
	m.finished_at = nil
}

// AddConferenceIDs adds the conference edge to Conference by ids.
func (m *CallMutation) AddConferenceIDs(ids ...int) {
	if m.conference == nil {
		m.conference = make(map[int]struct{})
	}
	for i := range ids {
		m.conference[ids[i]] = struct{}{}
	}
}

// RemoveConferenceIDs removes the conference edge to Conference by ids.
func (m *CallMutation) RemoveConferenceIDs(ids ...int) {
	if m.removedconference == nil {
		m.removedconference = make(map[int]struct{})
	}
	for i := range ids {
		m.removedconference[ids[i]] = struct{}{}
	}
}

// RemovedConference returns the removed ids of conference.
func (m *CallMutation) RemovedConferenceIDs() (ids []int) {
	for id := range m.removedconference {
		ids = append(ids, id)
	}
	return
}

// ConferenceIDs returns the conference ids in the mutation.
func (m *CallMutation) ConferenceIDs() (ids []int) {
	for id := range m.conference {
		ids = append(ids, id)
	}
	return
}

// ResetConference reset all changes of the "conference" edge.
func (m *CallMutation) ResetConference() {
	m.conference = nil
	m.removedconference = nil
}

// Op returns the operation name.
func (m *CallMutation) Op() Op {
	return m.op
}

// Type returns the node type of this mutation (Call).
func (m *CallMutation) Type() string {
	return m.typ
}

// Fields returns all fields that were changed during
// this mutation. Note that, in order to get all numeric
// fields that were in/decremented, call AddedFields().
func (m *CallMutation) Fields() []string {
	fields := make([]string, 0, 2)
	if m.started_at != nil {
		fields = append(fields, call.FieldStartedAt)
	}
	if m.finished_at != nil {
		fields = append(fields, call.FieldFinishedAt)
	}
	return fields
}

// Field returns the value of a field with the given name.
// The second boolean value indicates that this field was
// not set, or was not define in the schema.
func (m *CallMutation) Field(name string) (ent.Value, bool) {
	switch name {
	case call.FieldStartedAt:
		return m.StartedAt()
	case call.FieldFinishedAt:
		return m.FinishedAt()
	}
	return nil, false
}

// OldField returns the old value of the field from the database.
// An error is returned if the mutation operation is not UpdateOne,
// or the query to the database was failed.
func (m *CallMutation) OldField(ctx context.Context, name string) (ent.Value, error) {
	switch name {
	case call.FieldStartedAt:
		return m.OldStartedAt(ctx)
	case call.FieldFinishedAt:
		return m.OldFinishedAt(ctx)
	}
	return nil, fmt.Errorf("unknown Call field %s", name)
}

// SetField sets the value for the given name. It returns an
// error if the field is not defined in the schema, or if the
// type mismatch the field type.
func (m *CallMutation) SetField(name string, value ent.Value) error {
	switch name {
	case call.FieldStartedAt:
		v, ok := value.(time.Time)
		if !ok {
			return fmt.Errorf("unexpected type %T for field %s", value, name)
		}
		m.SetStartedAt(v)
		return nil
	case call.FieldFinishedAt:
		v, ok := value.(time.Time)
		if !ok {
			return fmt.Errorf("unexpected type %T for field %s", value, name)
		}
		m.SetFinishedAt(v)
		return nil
	}
	return fmt.Errorf("unknown Call field %s", name)
}

// AddedFields returns all numeric fields that were incremented
// or decremented during this mutation.
func (m *CallMutation) AddedFields() []string {
	return nil
}

// AddedField returns the numeric value that was in/decremented
// from a field with the given name. The second value indicates
// that this field was not set, or was not define in the schema.
func (m *CallMutation) AddedField(name string) (ent.Value, bool) {
	return nil, false
}

// AddField adds the value for the given name. It returns an
// error if the field is not defined in the schema, or if the
// type mismatch the field type.
func (m *CallMutation) AddField(name string, value ent.Value) error {
	switch name {
	}
	return fmt.Errorf("unknown Call numeric field %s", name)
}

// ClearedFields returns all nullable fields that were cleared
// during this mutation.
func (m *CallMutation) ClearedFields() []string {
	return nil
}

// FieldCleared returns a boolean indicates if this field was
// cleared in this mutation.
func (m *CallMutation) FieldCleared(name string) bool {
	_, ok := m.clearedFields[name]
	return ok
}

// ClearField clears the value for the given name. It returns an
// error if the field is not defined in the schema.
func (m *CallMutation) ClearField(name string) error {
	return fmt.Errorf("unknown Call nullable field %s", name)
}

// ResetField resets all changes in the mutation regarding the
// given field name. It returns an error if the field is not
// defined in the schema.
func (m *CallMutation) ResetField(name string) error {
	switch name {
	case call.FieldStartedAt:
		m.ResetStartedAt()
		return nil
	case call.FieldFinishedAt:
		m.ResetFinishedAt()
		return nil
	}
	return fmt.Errorf("unknown Call field %s", name)
}

// AddedEdges returns all edge names that were set/added in this
// mutation.
func (m *CallMutation) AddedEdges() []string {
	edges := make([]string, 0, 1)
	if m.conference != nil {
		edges = append(edges, call.EdgeConference)
	}
	return edges
}

// AddedIDs returns all ids (to other nodes) that were added for
// the given edge name.
func (m *CallMutation) AddedIDs(name string) []ent.Value {
	switch name {
	case call.EdgeConference:
		ids := make([]ent.Value, 0, len(m.conference))
		for id := range m.conference {
			ids = append(ids, id)
		}
		return ids
	}
	return nil
}

// RemovedEdges returns all edge names that were removed in this
// mutation.
func (m *CallMutation) RemovedEdges() []string {
	edges := make([]string, 0, 1)
	if m.removedconference != nil {
		edges = append(edges, call.EdgeConference)
	}
	return edges
}

// RemovedIDs returns all ids (to other nodes) that were removed for
// the given edge name.
func (m *CallMutation) RemovedIDs(name string) []ent.Value {
	switch name {
	case call.EdgeConference:
		ids := make([]ent.Value, 0, len(m.removedconference))
		for id := range m.removedconference {
			ids = append(ids, id)
		}
		return ids
	}
	return nil
}

// ClearedEdges returns all edge names that were cleared in this
// mutation.
func (m *CallMutation) ClearedEdges() []string {
	edges := make([]string, 0, 1)
	return edges
}

// EdgeCleared returns a boolean indicates if this edge was
// cleared in this mutation.
func (m *CallMutation) EdgeCleared(name string) bool {
	switch name {
	}
	return false
}

// ClearEdge clears the value for the given name. It returns an
// error if the edge name is not defined in the schema.
func (m *CallMutation) ClearEdge(name string) error {
	switch name {
	}
	return fmt.Errorf("unknown Call unique edge %s", name)
}

// ResetEdge resets all changes in the mutation regarding the
// given edge name. It returns an error if the edge is not
// defined in the schema.
func (m *CallMutation) ResetEdge(name string) error {
	switch name {
	case call.EdgeConference:
		m.ResetConference()
		return nil
	}
	return fmt.Errorf("unknown Call edge %s", name)
}

// ConferenceMutation represents an operation that mutate the Conferences
// nodes in the graph.
type ConferenceMutation struct {
	config
	op            Op
	typ           string
	id            *int
	clearedFields map[string]struct{}
	users         map[int]struct{}
	removedusers  map[int]struct{}
	calls         map[int]struct{}
	removedcalls  map[int]struct{}
	done          bool
	oldValue      func(context.Context) (*Conference, error)
}

var _ ent.Mutation = (*ConferenceMutation)(nil)

// conferenceOption allows to manage the mutation configuration using functional options.
type conferenceOption func(*ConferenceMutation)

// newConferenceMutation creates new mutation for $n.Name.
func newConferenceMutation(c config, op Op, opts ...conferenceOption) *ConferenceMutation {
	m := &ConferenceMutation{
		config:        c,
		op:            op,
		typ:           TypeConference,
		clearedFields: make(map[string]struct{}),
	}
	for _, opt := range opts {
		opt(m)
	}
	return m
}

// withConferenceID sets the id field of the mutation.
func withConferenceID(id int) conferenceOption {
	return func(m *ConferenceMutation) {
		var (
			err   error
			once  sync.Once
			value *Conference
		)
		m.oldValue = func(ctx context.Context) (*Conference, error) {
			once.Do(func() {
				if m.done {
					err = fmt.Errorf("querying old values post mutation is not allowed")
				} else {
					value, err = m.Client().Conference.Get(ctx, id)
				}
			})
			return value, err
		}
		m.id = &id
	}
}

// withConference sets the old Conference of the mutation.
func withConference(node *Conference) conferenceOption {
	return func(m *ConferenceMutation) {
		m.oldValue = func(context.Context) (*Conference, error) {
			return node, nil
		}
		m.id = &node.ID
	}
}

// Client returns a new `ent.Client` from the mutation. If the mutation was
// executed in a transaction (ent.Tx), a transactional client is returned.
func (m ConferenceMutation) Client() *Client {
	client := &Client{config: m.config}
	client.init()
	return client
}

// Tx returns an `ent.Tx` for mutations that were executed in transactions;
// it returns an error otherwise.
func (m ConferenceMutation) Tx() (*Tx, error) {
	if _, ok := m.driver.(*txDriver); !ok {
		return nil, fmt.Errorf("ent: mutation is not running in a transaction")
	}
	tx := &Tx{config: m.config}
	tx.init()
	return tx, nil
}

// ID returns the id value in the mutation. Note that, the id
// is available only if it was provided to the builder.
func (m *ConferenceMutation) ID() (id int, exists bool) {
	if m.id == nil {
		return
	}
	return *m.id, true
}

// AddUserIDs adds the users edge to User by ids.
func (m *ConferenceMutation) AddUserIDs(ids ...int) {
	if m.users == nil {
		m.users = make(map[int]struct{})
	}
	for i := range ids {
		m.users[ids[i]] = struct{}{}
	}
}

// RemoveUserIDs removes the users edge to User by ids.
func (m *ConferenceMutation) RemoveUserIDs(ids ...int) {
	if m.removedusers == nil {
		m.removedusers = make(map[int]struct{})
	}
	for i := range ids {
		m.removedusers[ids[i]] = struct{}{}
	}
}

// RemovedUsers returns the removed ids of users.
func (m *ConferenceMutation) RemovedUsersIDs() (ids []int) {
	for id := range m.removedusers {
		ids = append(ids, id)
	}
	return
}

// UsersIDs returns the users ids in the mutation.
func (m *ConferenceMutation) UsersIDs() (ids []int) {
	for id := range m.users {
		ids = append(ids, id)
	}
	return
}

// ResetUsers reset all changes of the "users" edge.
func (m *ConferenceMutation) ResetUsers() {
	m.users = nil
	m.removedusers = nil
}

// AddCallIDs adds the calls edge to Call by ids.
func (m *ConferenceMutation) AddCallIDs(ids ...int) {
	if m.calls == nil {
		m.calls = make(map[int]struct{})
	}
	for i := range ids {
		m.calls[ids[i]] = struct{}{}
	}
}

// RemoveCallIDs removes the calls edge to Call by ids.
func (m *ConferenceMutation) RemoveCallIDs(ids ...int) {
	if m.removedcalls == nil {
		m.removedcalls = make(map[int]struct{})
	}
	for i := range ids {
		m.removedcalls[ids[i]] = struct{}{}
	}
}

// RemovedCalls returns the removed ids of calls.
func (m *ConferenceMutation) RemovedCallsIDs() (ids []int) {
	for id := range m.removedcalls {
		ids = append(ids, id)
	}
	return
}

// CallsIDs returns the calls ids in the mutation.
func (m *ConferenceMutation) CallsIDs() (ids []int) {
	for id := range m.calls {
		ids = append(ids, id)
	}
	return
}

// ResetCalls reset all changes of the "calls" edge.
func (m *ConferenceMutation) ResetCalls() {
	m.calls = nil
	m.removedcalls = nil
}

// Op returns the operation name.
func (m *ConferenceMutation) Op() Op {
	return m.op
}

// Type returns the node type of this mutation (Conference).
func (m *ConferenceMutation) Type() string {
	return m.typ
}

// Fields returns all fields that were changed during
// this mutation. Note that, in order to get all numeric
// fields that were in/decremented, call AddedFields().
func (m *ConferenceMutation) Fields() []string {
	fields := make([]string, 0, 0)
	return fields
}

// Field returns the value of a field with the given name.
// The second boolean value indicates that this field was
// not set, or was not define in the schema.
func (m *ConferenceMutation) Field(name string) (ent.Value, bool) {
	return nil, false
}

// OldField returns the old value of the field from the database.
// An error is returned if the mutation operation is not UpdateOne,
// or the query to the database was failed.
func (m *ConferenceMutation) OldField(ctx context.Context, name string) (ent.Value, error) {
	return nil, fmt.Errorf("unknown Conference field %s", name)
}

// SetField sets the value for the given name. It returns an
// error if the field is not defined in the schema, or if the
// type mismatch the field type.
func (m *ConferenceMutation) SetField(name string, value ent.Value) error {
	switch name {
	}
	return fmt.Errorf("unknown Conference field %s", name)
}

// AddedFields returns all numeric fields that were incremented
// or decremented during this mutation.
func (m *ConferenceMutation) AddedFields() []string {
	return nil
}

// AddedField returns the numeric value that was in/decremented
// from a field with the given name. The second value indicates
// that this field was not set, or was not define in the schema.
func (m *ConferenceMutation) AddedField(name string) (ent.Value, bool) {
	return nil, false
}

// AddField adds the value for the given name. It returns an
// error if the field is not defined in the schema, or if the
// type mismatch the field type.
func (m *ConferenceMutation) AddField(name string, value ent.Value) error {
	return fmt.Errorf("unknown Conference numeric field %s", name)
}

// ClearedFields returns all nullable fields that were cleared
// during this mutation.
func (m *ConferenceMutation) ClearedFields() []string {
	return nil
}

// FieldCleared returns a boolean indicates if this field was
// cleared in this mutation.
func (m *ConferenceMutation) FieldCleared(name string) bool {
	_, ok := m.clearedFields[name]
	return ok
}

// ClearField clears the value for the given name. It returns an
// error if the field is not defined in the schema.
func (m *ConferenceMutation) ClearField(name string) error {
	return fmt.Errorf("unknown Conference nullable field %s", name)
}

// ResetField resets all changes in the mutation regarding the
// given field name. It returns an error if the field is not
// defined in the schema.
func (m *ConferenceMutation) ResetField(name string) error {
	return fmt.Errorf("unknown Conference field %s", name)
}

// AddedEdges returns all edge names that were set/added in this
// mutation.
func (m *ConferenceMutation) AddedEdges() []string {
	edges := make([]string, 0, 2)
	if m.users != nil {
		edges = append(edges, conference.EdgeUsers)
	}
	if m.calls != nil {
		edges = append(edges, conference.EdgeCalls)
	}
	return edges
}

// AddedIDs returns all ids (to other nodes) that were added for
// the given edge name.
func (m *ConferenceMutation) AddedIDs(name string) []ent.Value {
	switch name {
	case conference.EdgeUsers:
		ids := make([]ent.Value, 0, len(m.users))
		for id := range m.users {
			ids = append(ids, id)
		}
		return ids
	case conference.EdgeCalls:
		ids := make([]ent.Value, 0, len(m.calls))
		for id := range m.calls {
			ids = append(ids, id)
		}
		return ids
	}
	return nil
}

// RemovedEdges returns all edge names that were removed in this
// mutation.
func (m *ConferenceMutation) RemovedEdges() []string {
	edges := make([]string, 0, 2)
	if m.removedusers != nil {
		edges = append(edges, conference.EdgeUsers)
	}
	if m.removedcalls != nil {
		edges = append(edges, conference.EdgeCalls)
	}
	return edges
}

// RemovedIDs returns all ids (to other nodes) that were removed for
// the given edge name.
func (m *ConferenceMutation) RemovedIDs(name string) []ent.Value {
	switch name {
	case conference.EdgeUsers:
		ids := make([]ent.Value, 0, len(m.removedusers))
		for id := range m.removedusers {
			ids = append(ids, id)
		}
		return ids
	case conference.EdgeCalls:
		ids := make([]ent.Value, 0, len(m.removedcalls))
		for id := range m.removedcalls {
			ids = append(ids, id)
		}
		return ids
	}
	return nil
}

// ClearedEdges returns all edge names that were cleared in this
// mutation.
func (m *ConferenceMutation) ClearedEdges() []string {
	edges := make([]string, 0, 2)
	return edges
}

// EdgeCleared returns a boolean indicates if this edge was
// cleared in this mutation.
func (m *ConferenceMutation) EdgeCleared(name string) bool {
	switch name {
	}
	return false
}

// ClearEdge clears the value for the given name. It returns an
// error if the edge name is not defined in the schema.
func (m *ConferenceMutation) ClearEdge(name string) error {
	switch name {
	}
	return fmt.Errorf("unknown Conference unique edge %s", name)
}

// ResetEdge resets all changes in the mutation regarding the
// given edge name. It returns an error if the edge is not
// defined in the schema.
func (m *ConferenceMutation) ResetEdge(name string) error {
	switch name {
	case conference.EdgeUsers:
		m.ResetUsers()
		return nil
	case conference.EdgeCalls:
		m.ResetCalls()
		return nil
	}
	return fmt.Errorf("unknown Conference edge %s", name)
}

// UserMutation represents an operation that mutate the Users
// nodes in the graph.
type UserMutation struct {
	config
	op                 Op
	typ                string
	id                 *int
	login              *string
	password           *string
	clearedFields      map[string]struct{}
	conferences        map[int]struct{}
	removedconferences map[int]struct{}
	done               bool
	oldValue           func(context.Context) (*User, error)
}

var _ ent.Mutation = (*UserMutation)(nil)

// userOption allows to manage the mutation configuration using functional options.
type userOption func(*UserMutation)

// newUserMutation creates new mutation for $n.Name.
func newUserMutation(c config, op Op, opts ...userOption) *UserMutation {
	m := &UserMutation{
		config:        c,
		op:            op,
		typ:           TypeUser,
		clearedFields: make(map[string]struct{}),
	}
	for _, opt := range opts {
		opt(m)
	}
	return m
}

// withUserID sets the id field of the mutation.
func withUserID(id int) userOption {
	return func(m *UserMutation) {
		var (
			err   error
			once  sync.Once
			value *User
		)
		m.oldValue = func(ctx context.Context) (*User, error) {
			once.Do(func() {
				if m.done {
					err = fmt.Errorf("querying old values post mutation is not allowed")
				} else {
					value, err = m.Client().User.Get(ctx, id)
				}
			})
			return value, err
		}
		m.id = &id
	}
}

// withUser sets the old User of the mutation.
func withUser(node *User) userOption {
	return func(m *UserMutation) {
		m.oldValue = func(context.Context) (*User, error) {
			return node, nil
		}
		m.id = &node.ID
	}
}

// Client returns a new `ent.Client` from the mutation. If the mutation was
// executed in a transaction (ent.Tx), a transactional client is returned.
func (m UserMutation) Client() *Client {
	client := &Client{config: m.config}
	client.init()
	return client
}

// Tx returns an `ent.Tx` for mutations that were executed in transactions;
// it returns an error otherwise.
func (m UserMutation) Tx() (*Tx, error) {
	if _, ok := m.driver.(*txDriver); !ok {
		return nil, fmt.Errorf("ent: mutation is not running in a transaction")
	}
	tx := &Tx{config: m.config}
	tx.init()
	return tx, nil
}

// ID returns the id value in the mutation. Note that, the id
// is available only if it was provided to the builder.
func (m *UserMutation) ID() (id int, exists bool) {
	if m.id == nil {
		return
	}
	return *m.id, true
}

// SetLogin sets the login field.
func (m *UserMutation) SetLogin(s string) {
	m.login = &s
}

// Login returns the login value in the mutation.
func (m *UserMutation) Login() (r string, exists bool) {
	v := m.login
	if v == nil {
		return
	}
	return *v, true
}

// OldLogin returns the old login value of the User.
// If the User object wasn't provided to the builder, the object is fetched
// from the database.
// An error is returned if the mutation operation is not UpdateOne, or database query fails.
func (m *UserMutation) OldLogin(ctx context.Context) (v string, err error) {
	if !m.op.Is(OpUpdateOne) {
		return v, fmt.Errorf("OldLogin is allowed only on UpdateOne operations")
	}
	if m.id == nil || m.oldValue == nil {
		return v, fmt.Errorf("OldLogin requires an ID field in the mutation")
	}
	oldValue, err := m.oldValue(ctx)
	if err != nil {
		return v, fmt.Errorf("querying old value for OldLogin: %w", err)
	}
	return oldValue.Login, nil
}

// ResetLogin reset all changes of the "login" field.
func (m *UserMutation) ResetLogin() {
	m.login = nil
}

// SetPassword sets the password field.
func (m *UserMutation) SetPassword(s string) {
	m.password = &s
}

// Password returns the password value in the mutation.
func (m *UserMutation) Password() (r string, exists bool) {
	v := m.password
	if v == nil {
		return
	}
	return *v, true
}

// OldPassword returns the old password value of the User.
// If the User object wasn't provided to the builder, the object is fetched
// from the database.
// An error is returned if the mutation operation is not UpdateOne, or database query fails.
func (m *UserMutation) OldPassword(ctx context.Context) (v string, err error) {
	if !m.op.Is(OpUpdateOne) {
		return v, fmt.Errorf("OldPassword is allowed only on UpdateOne operations")
	}
	if m.id == nil || m.oldValue == nil {
		return v, fmt.Errorf("OldPassword requires an ID field in the mutation")
	}
	oldValue, err := m.oldValue(ctx)
	if err != nil {
		return v, fmt.Errorf("querying old value for OldPassword: %w", err)
	}
	return oldValue.Password, nil
}

// ResetPassword reset all changes of the "password" field.
func (m *UserMutation) ResetPassword() {
	m.password = nil
}

// AddConferenceIDs adds the conferences edge to Conference by ids.
func (m *UserMutation) AddConferenceIDs(ids ...int) {
	if m.conferences == nil {
		m.conferences = make(map[int]struct{})
	}
	for i := range ids {
		m.conferences[ids[i]] = struct{}{}
	}
}

// RemoveConferenceIDs removes the conferences edge to Conference by ids.
func (m *UserMutation) RemoveConferenceIDs(ids ...int) {
	if m.removedconferences == nil {
		m.removedconferences = make(map[int]struct{})
	}
	for i := range ids {
		m.removedconferences[ids[i]] = struct{}{}
	}
}

// RemovedConferences returns the removed ids of conferences.
func (m *UserMutation) RemovedConferencesIDs() (ids []int) {
	for id := range m.removedconferences {
		ids = append(ids, id)
	}
	return
}

// ConferencesIDs returns the conferences ids in the mutation.
func (m *UserMutation) ConferencesIDs() (ids []int) {
	for id := range m.conferences {
		ids = append(ids, id)
	}
	return
}

// ResetConferences reset all changes of the "conferences" edge.
func (m *UserMutation) ResetConferences() {
	m.conferences = nil
	m.removedconferences = nil
}

// Op returns the operation name.
func (m *UserMutation) Op() Op {
	return m.op
}

// Type returns the node type of this mutation (User).
func (m *UserMutation) Type() string {
	return m.typ
}

// Fields returns all fields that were changed during
// this mutation. Note that, in order to get all numeric
// fields that were in/decremented, call AddedFields().
func (m *UserMutation) Fields() []string {
	fields := make([]string, 0, 2)
	if m.login != nil {
		fields = append(fields, user.FieldLogin)
	}
	if m.password != nil {
		fields = append(fields, user.FieldPassword)
	}
	return fields
}

// Field returns the value of a field with the given name.
// The second boolean value indicates that this field was
// not set, or was not define in the schema.
func (m *UserMutation) Field(name string) (ent.Value, bool) {
	switch name {
	case user.FieldLogin:
		return m.Login()
	case user.FieldPassword:
		return m.Password()
	}
	return nil, false
}

// OldField returns the old value of the field from the database.
// An error is returned if the mutation operation is not UpdateOne,
// or the query to the database was failed.
func (m *UserMutation) OldField(ctx context.Context, name string) (ent.Value, error) {
	switch name {
	case user.FieldLogin:
		return m.OldLogin(ctx)
	case user.FieldPassword:
		return m.OldPassword(ctx)
	}
	return nil, fmt.Errorf("unknown User field %s", name)
}

// SetField sets the value for the given name. It returns an
// error if the field is not defined in the schema, or if the
// type mismatch the field type.
func (m *UserMutation) SetField(name string, value ent.Value) error {
	switch name {
	case user.FieldLogin:
		v, ok := value.(string)
		if !ok {
			return fmt.Errorf("unexpected type %T for field %s", value, name)
		}
		m.SetLogin(v)
		return nil
	case user.FieldPassword:
		v, ok := value.(string)
		if !ok {
			return fmt.Errorf("unexpected type %T for field %s", value, name)
		}
		m.SetPassword(v)
		return nil
	}
	return fmt.Errorf("unknown User field %s", name)
}

// AddedFields returns all numeric fields that were incremented
// or decremented during this mutation.
func (m *UserMutation) AddedFields() []string {
	return nil
}

// AddedField returns the numeric value that was in/decremented
// from a field with the given name. The second value indicates
// that this field was not set, or was not define in the schema.
func (m *UserMutation) AddedField(name string) (ent.Value, bool) {
	return nil, false
}

// AddField adds the value for the given name. It returns an
// error if the field is not defined in the schema, or if the
// type mismatch the field type.
func (m *UserMutation) AddField(name string, value ent.Value) error {
	switch name {
	}
	return fmt.Errorf("unknown User numeric field %s", name)
}

// ClearedFields returns all nullable fields that were cleared
// during this mutation.
func (m *UserMutation) ClearedFields() []string {
	return nil
}

// FieldCleared returns a boolean indicates if this field was
// cleared in this mutation.
func (m *UserMutation) FieldCleared(name string) bool {
	_, ok := m.clearedFields[name]
	return ok
}

// ClearField clears the value for the given name. It returns an
// error if the field is not defined in the schema.
func (m *UserMutation) ClearField(name string) error {
	return fmt.Errorf("unknown User nullable field %s", name)
}

// ResetField resets all changes in the mutation regarding the
// given field name. It returns an error if the field is not
// defined in the schema.
func (m *UserMutation) ResetField(name string) error {
	switch name {
	case user.FieldLogin:
		m.ResetLogin()
		return nil
	case user.FieldPassword:
		m.ResetPassword()
		return nil
	}
	return fmt.Errorf("unknown User field %s", name)
}

// AddedEdges returns all edge names that were set/added in this
// mutation.
func (m *UserMutation) AddedEdges() []string {
	edges := make([]string, 0, 1)
	if m.conferences != nil {
		edges = append(edges, user.EdgeConferences)
	}
	return edges
}

// AddedIDs returns all ids (to other nodes) that were added for
// the given edge name.
func (m *UserMutation) AddedIDs(name string) []ent.Value {
	switch name {
	case user.EdgeConferences:
		ids := make([]ent.Value, 0, len(m.conferences))
		for id := range m.conferences {
			ids = append(ids, id)
		}
		return ids
	}
	return nil
}

// RemovedEdges returns all edge names that were removed in this
// mutation.
func (m *UserMutation) RemovedEdges() []string {
	edges := make([]string, 0, 1)
	if m.removedconferences != nil {
		edges = append(edges, user.EdgeConferences)
	}
	return edges
}

// RemovedIDs returns all ids (to other nodes) that were removed for
// the given edge name.
func (m *UserMutation) RemovedIDs(name string) []ent.Value {
	switch name {
	case user.EdgeConferences:
		ids := make([]ent.Value, 0, len(m.removedconferences))
		for id := range m.removedconferences {
			ids = append(ids, id)
		}
		return ids
	}
	return nil
}

// ClearedEdges returns all edge names that were cleared in this
// mutation.
func (m *UserMutation) ClearedEdges() []string {
	edges := make([]string, 0, 1)
	return edges
}

// EdgeCleared returns a boolean indicates if this edge was
// cleared in this mutation.
func (m *UserMutation) EdgeCleared(name string) bool {
	switch name {
	}
	return false
}

// ClearEdge clears the value for the given name. It returns an
// error if the edge name is not defined in the schema.
func (m *UserMutation) ClearEdge(name string) error {
	switch name {
	}
	return fmt.Errorf("unknown User unique edge %s", name)
}

// ResetEdge resets all changes in the mutation regarding the
// given edge name. It returns an error if the edge is not
// defined in the schema.
func (m *UserMutation) ResetEdge(name string) error {
	switch name {
	case user.EdgeConferences:
		m.ResetConferences()
		return nil
	}
	return fmt.Errorf("unknown User edge %s", name)
}
