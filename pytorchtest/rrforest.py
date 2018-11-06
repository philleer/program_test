"""
File:   rrforest.py
Author: Phil Lee
Email:  phillee2016@163.com
Github: https://github.com/philleer
Description: Random regression forest implementation
"""

from pyspark.ml import Pipeline
from pyspark.ml.regression import RandomForestRegressor
from pyspark.ml.feature import VectorIndexer
from pyspark.ml.evaluation import RegressionEvaluator

data = spark.read.format("libsvm").load("data/mllib/sample_libsvm_data.txt")

featureIndexer = VectorIndexer(inputCol="features",
        outputCol="indexedFeatures", maxCategories=4).fit(data)
(trainingData, testData) = data.randomSplit([0.7, 0.3])

rf = RandomForestRegressor(featureCol="indexedFeatures")

pipeline = Pipeline(stages=[featureIndexer, rf])

model = pipeline.fit(trainingData)

predictions = model.transform(testData)

predictions.select("prediction", "label", "features").show(5)

evaluator = RegressionEvaluator(labelCol="label", predictionCol="prediction",
        metricName="rmse")

rmse = evaluator.evaluate(predictions)
print("Root Mean Squared Error on test data = %g" % rmse)

rfmodel = model.stages[1]
print(rfModel)

