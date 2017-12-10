const DIMENSION = {
	width: 1000,
	height: 700,
	margin: {
		left: 100,
		right: 100,
		top: 100,
		bottom: 100
	}
};

DIMENSION.trueWidth = DIMENSION.width - (DIMENSION.margin.left + DIMENSION.margin.right);
DIMENSION.trueHeight = DIMENSION.height - (DIMENSION.margin.top + DIMENSION.margin.bottom);

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

	const categories = {};
	transformed.categories = categories;

	const years = new Set();
	transformed.years = years;

	for (let restaurant of data) {
		const category = restaurant.category;

		for (let q of restaurant.quarters) {
			const jsonDate = {};

			[jsonDate.year, jsonDate.month, jsonDate.day] = q.quarter.split('-').map(e => parseInt(e));

			q.quarter = jsonDate;

			years.add(q.quarter.year);
		}

		if (!categories[category]) {
			categories[category] = [restaurant];
		} else {
			categories[category].push(restaurant);
		}
	}

	return transformed;
};

loadData().then(([data]) => {
	init(CONTAINER);

	const transformed = transformData(data);

	window.transformed = transformed;
	window.data = data;

	const container = d3.select(CONTAINER);

	const colorScale = d3.scaleOrdinal()
		.range(d3.schemeCategory20)
		.domain(Object.keys(transformed.categories));

	const axisYearScale = d3.scaleBand();
	const axisQuarterScale = d3.scaleBand();

	const xScale = d3.scaleLinear()
		.range([0, DIMENSION.trueWidth])
		.domain(d3.extent(Array.from(transformed.years), d => d));
	const yScale = d3.scaleLinear()
		.range([DIMENSION.trueHeight, 0])
		.domain([1, 5]);

	const linesContainer = {};
	for (let k of Object.keys(transformed.categories)) {
		linesContainer[k] = container.append('g')
			.attr('class', `category-${k}`);
	}

	for (let restaurant of data) {
		const line = d3.line()
			.x(d => xScale(d.quarter.year))
			.y(d => yScale(d.rating));

		linesContainer[restaurant.category].append('path')
			.datum(restaurant.quarters)
			.attr('fill', 'none')
			.attr('stroke', colorScale(restaurant.category))
			.attr('d', line);
	}
});
