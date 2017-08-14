import requests

def getData(url, party):
	request_data = requests.get(url)
	request_json = request_data.json()

	print(party)
	for x in request_json['estimates']:
		if (x['first_name']):
			print('%s %s: %s%%' % (x['first_name'], x['last_name'], x['value']))
		elif (x['choice']):
			print('%s: %s%%' % (x['choice'], x['value']))
	print()

getData('http://elections.huffingtonpost.com/pollster/api/charts/2016-national-democratic-primary', 'Democrat')
getData('http://elections.huffingtonpost.com/pollster/api/charts/2016-national-gop-primary', 'Republican')
