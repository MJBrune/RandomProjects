require 'sinatra'
require 'mongo'
require 'json'

get '/playing/:project' do
  client = Mongo::Connection.new
  db = client['prototypeResponses'] 
  coll = db[params[:project]]
  data = {'ip' => request.ip, 'token' => SecureRandom.hex(), 'time' => Time.now,
    'agent' => request.user_agent}
  coll.insert(data)
  "#{data['token']}"
end

before do
  next unless request.post?
  @req_data = JSON.parse(request.body.read.to_s)
end

post '/addCheckPoint/:project' do
  client = Mongo::Connection.new
  db = client['prototypeResponses'] 
  coll = db[params[:project]]
  query = {'token' => @req_data['token']}
  update = {"$addToSet" => @req_data['checkpoints']}
  coll.update(query, update)
  "#{@req_data['token']}"
end