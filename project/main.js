const DIMENSION = {
	width: 1000,
	height: 700,
	margin: {
		x: 100,
		y: 100
	}
};

const CONTAINER = '#chart';

const loadData = () => {
	return new Promise((resolve, reject) => {
		d3.queue()
			.defer(d3.json, 'Las Vegas Business.json')
			.await((err, ...data) => {
				if (err) {
					reject(err);
				} else {
					resolve(data);
				}
			});
	});
};

const init = (container) => {
	d3.select(CONTAINER)
		.attr('width', DIMENSION.width)
		.attr('height', DIMENSION.height);
};

const transformData = (data) => {
	const transformed = {};

	return transformed;
};

loadData().then(([data]) => {
	init(CONTAINER);

	const transformData = transformData(data);

	const container = d3.select(CONTAINER);
});
